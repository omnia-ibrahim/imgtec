<?php

use Doctrine\Common\Cache\ArrayCache;
class FDWDatastoreServicesImpl extends FDWFlowCloudClientImpl implements FDWDatastoreServices
{
	/**
	 * This property will be populated only if all datastores were returned in a single page.
	 * So this is highly dependent on the page size specified when the call was made
	 *  
	 * @var Lounge2_Datastores
	 */
	protected  $datastores = null;	
		
	/**
	 * Create an instance of FDWDatastoreServicesImpl and initialize the flowCloud variable
	 * 
	 * The authoCredentials argument should be an associative array that contains the following keys:
	 * 
	 * - oauth_key
	 * - oauth_secret
	 * 
	 * @param $authoCredentials 
	 * @param $DrupalUser
	 */
	public function __construct(array $authoCredentials=array(), $DrupalUser=null)
	{
		parent::__construct($authoCredentials, $DrupalUser);
	}

	/**
	 * Yields all system resources currently reserved for this object 
	 */
	public function __destruct()
	{
		parent::__destruct();
	}
	
	/**
	 * Return a paged list of all available datastores
	 * 
	 * @param int $pageNumber
	 * @param int $pageSize
	 * @param int $assemble
	 * 
	 * @return mixed 
	 */
	protected function findDatastores($pageNumber=1, $pageSize=20, $assemble = false)
	{
		$datastoreContainer = array('items' => array(), 'pagecount' => 0, 'canCreate' => false);
		
		if (isset($pageNumber) && isset($pageSize)) 
		{
			$startIndex = $this->getPagerStartIndex($pageNumber, $pageSize);
			/**
			 * @var Lounge2_Datastores
			 */
			$datastores = null;		
			$pager = null;
			$recordCount = 0;
			
			/**
			if (!isset($this->datastores)) 
			{
				$datastores =  $this->flowCloud->admin_get_datastores($startIndex, $pageSize);
			}
			else
			{
				$datastores = $this->datastores;
			}
			**/
			
			if ($this->setDatastoresResourceBundle($startIndex, $pageSize)) 
			{
				$datastores = $this->datastores;
						
				if (isset($datastores) && (!$datastores->is_empty_object())) 
				{
					$recordCount = $datastores->count();
					if ($recordCount) 
					{
						$pager = $this->buildPagerMetadata($recordCount, $pageNumber, $pageSize);
						$datastoreContainer['pagecount'] = $pager['pagecount'];
						/**
						 * cache the user's device types resource bundle if it all fits in one page 
						 */			
						if ($pager['pagecount'] == 1) 
						{
							$this->datastores = $datastores;
						}
						
						if ($assemble) 
						{
							foreach ($datastores as $ds) 
							{
								$datastoreContainer['items'][] = $this->assembleDatastore($ds);
							}					
						}
						else
						{
							$datastoreContainer['items'] = $datastores;
						}
	
					}
					elseif (!$assemble)
					{
						$datastoreContainer['items'] = $datastores;
					}
					
					$datastoreContainer['canCreate'] = $datastores->canCreateDatastore();
				}				
			}

		}		
		
		return $datastoreContainer;
	}
	
	/**
	 * Return the datastore identified by the supplied by the name or null otherwise
	 * 
	 * @param string $name
	 * 
	 * @return Lounge2_DataStore
	 */
	public function findDatastoreByName($name = null, $pageNumber=1)
	{
		$pageSize = 100;
		/**
		 * @var Lounge2_DataStores
		 */
		$datastores = null;
		/**
		 * @var Lounge2_DataStore
		 */
		$foundDatastore = null;
		$recordCount = 0;
		
		
		if (isset($name)) 
		{
			$datastoresContainer = $this->findDatastores($pageNumber, $pageSize, false);
			$datastores = $datastoresContainer['items'];
			
			if (isset($datastores) && ($datastores instanceof Lounge2_DataStores) && (!$datastores->is_empty_object())) 
			{
				$recordCount = $datastores->count();
				$pager = $this->buildPagerMetadata($recordCount, $pageNumber, $pageSize);
				if ($recordCount) 
				{
					/**
					 * Search for the datastore
					 */
					foreach ($datastores as $ds) 
					{
						if ($ds->Name == $name) 
						{
							$foundDatastore= $ds;
							break;
						}
					}
					
					/**
					 * If the datastore was not found on this page, check if there are multiple
					 * pages and make a recursive call to this function to search the next page.
					 */
					if (!isset($foundDatastore)) 
					{
						if ($pager['pagecount'] > $pageNumber) 
						{
							$this->findDatastoreByName($name, ($pageNumber + 1));
						}
					}
				}				
			}
		}

		return $foundDatastore;
	}
	
	/**
	 * Return an array representation of a Lounge2_DataStore object
	 * 
	 * @param Lounge2_DataStore $ds
	 * @return array
	 */
	protected function assembleDatastore(Lounge2_DataStore $ds)
	{
		$datastore = null;
		if (isset($ds) && (!$ds->is_empty_object())) 
		{
			$isDeviceDatastore = (strtolower($ds->IsDeviceDataStore) == 'true') ? true : false;
			$isUserDatastore = (strtolower($ds->IsUserDataStore) == 'true') ? true : false;
			
			$datastore = array(
				'Name' => $ds->Name,
				'IsDeviceDataStore' => $isDeviceDatastore,
				'IsUserDataStore' => $isUserDatastore,
				'CanDelete' => $ds->canDelete()
			);
		}
		
		return $datastore;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see FDWDatastoreServices::getDatastores()
	 */
	public function getDatastores($pageNumber=1, $pageSize=20)
	{
		return $this->findDatastores($pageNumber, $pageSize, true);
	}
	
	/**
	 * (non-PHPdoc)
	 * @see FDWDatastoreServices::getDatastore()
	 */
	public function getDatastore($name=null)
	{
		$datastore = null;
		if (isset($name)) 
		{
			$ds = $this->findDatastoreByName($name, 1);
			if ( isset($ds) && ($ds instanceof Lounge2_DataStore) && (!$ds->is_empty_object())) 
			{
				$datastore = $this->assembleDatastore($ds);
			}
		}
		
		return $datastore;			
	}
	
	/**
	 * (non-PHPdoc)
	 * @see FDWDatastoreServices::createDatastore()
	 */
	public function createDatastore($name=null, $isDeviceDatastore=true, $isUserDatastore=true)
	{
		$datastoreCreated = false;
		if (isset($name)) 
		{
			/**
			 * @var Lounge2_DataStores
			 */
			$datastores = null;
			$datastoresContainer = $this->findDatastores(1, 1, false);
			$datastores = $datastoresContainer['items'];
			if (isset($datastores) && ($datastores instanceof Lounge2_DataStores) && (!$datastores->is_empty_object())) 
			{
				$responseCode = $datastores->createDatastore($name, $isDeviceDatastore, $isUserDatastore);
				$datastoreCreated = ($responseCode == 200) ? true : false;
			}			
		}
		
		return $datastoreCreated;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see FDWDatastoreServices::deleteDatastore()
	 */
	public function deleteDatastore($name = null)
	{
		$datastoreDeleted = false;
		if (isset($name)) 
		{
			$datastore = $this->findDatastoreByName($name, 1);
			if ( isset($datastore) && ($datastore instanceof Lounge2_DataStore) && (!$datastore->is_empty_object())) 
			{
				$datastoreDeleted = $datastore->delete();
			}				
		}
		
		return $datastoreDeleted;
	}

	/**
	 * Load the datastores resource bundle that will be used by this object.
	 * 
	 * Datastore admin features are currently available in the new multi-tenant system that we are not yet using
	 * and hence are not accessible. But all these features can be accessed in the current system but going through 
	 * the tenant admin's user resource bundles. We can easily make the switch to using the new end points as this is 
	 * transparent to the client methods. 
	 */
	protected function setDatastoresResourceBundle($startIndex = 0, $pageSize = 50)
	{
		$resourceBundleLoaded = false;
		
		if (!isset($this->datastores)) 
		{
			if ($this->setUserDetails()) 
			{
				/**
				 * Replace the below call with the following when multi-tenant support is in place
				 * 
				 * $this->flowCloud->admin_get_datastores($startIndex, $pageSize);
				 * 
				 * @var unknown_type
				 */
				$datastores = $this->userDetails->get_datastores($startIndex, $pageSize);
				if ( (isset($datastores)) && ($datastores instanceof Lounge2_DataStores) && (!$datastores->is_empty_object())) 
				{
					$this->datastores = $datastores;
					$resourceBundleLoaded = true;
				}	
			}
		}
		else
		{
			$resourceBundleLoaded = true;
		}
		
		return $resourceBundleLoaded;
	}
}