<?php

class FDWDeviceTypeServicesImpl extends FDWFlowCloudClientImpl implements FDWDeviceTypeServices
{
	/**
	 * This property will be populated only if all device types were returned in a single page.
	 * So this is highly dependent on the page size specified when the call was made
	 * 
	 * @var Lounge2_Devices
	 */
	protected $devices = null;
	
	/**
	 * This property will be populated only if all device types were returned in a single page.
	 * So this is highly dependent on the page size specified when the call was made
	 *  
	 * @var Lounge2_DeviceTypes
	 */
	protected  $deviceTypes = null;	
	
	/**
	 * Create an instance of FDWDeviceTypeServicesImpl and initialize the flowCloud variable
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
	 * Return a paged list of all available datatypes
	 * 
	 * @param int $pageNumber
	 * @param int $pageSize
	 * @param int $assemble
	 * 
	 * @return mixed 
	 */	
	protected function findDeviceTypes($pageNumber=1, $pageSize=20, $assemble = false)
	{
		$deviceTypesContainer = array('items' => array(), 'pagecount' => 0);
		
		if (isset($pageNumber) && isset($pageSize)) 
		{
			$startIndex = $this->getPagerStartIndex($pageNumber, $pageSize);
			/**
			 * @var Lounge2_Devices
			 */
			$devices = null;		
			/**
			 * @var Lounge2_DeviceTypes
			 */
			$deviceTypes = null;
			$pager = null;
			$recordCount = 0;

			if (!isset($this->deviceTypes)) 
			{
				if (!isset($this->devices)) 
				{
					/**
					 * In this case, we are going through the devices link only to get the the 
					 * device types link so we do not need more than 1 device in the list
					 */
					$devices = $this->flowCloud->admin_get_devices($startIndex, 1);
					if (isset($devices) && (!$devices->is_empty_object())) 
					{
						$deviceTypes = $devices->get_device_types($startIndex, $pageSize);
					}
				}
				else
				{
					$deviceTypes = $this->devices->get_device_types($startIndex, $pageSize);
				}
			}
			else
			{
				$deviceTypes = $this->deviceTypes;
			}
			
			if (isset($deviceTypes) && (!$deviceTypes->is_empty_object())) 
			{
				$recordCount = $deviceTypes->count();
				if ($recordCount) 
				{
					$pager = $this->buildPagerMetadata($recordCount, $pageNumber, $pageSize);
					$deviceTypesContainer['pagecount'] = $pager['pagecount'];
					/**
					 * cache the user's device types resource bundle if it all fits in one page 
					 */			
					if ($pager['pagecount'] == 1) 
					{
						$this->deviceTypes = $deviceTypes;
					}
					
					if ($assemble) 
					{
						foreach ($deviceTypes as $dt) 
						{
							$deviceTypesContainer['items'][] = $this->assembleDeviceType($dt);
						}					
					}
					else
					{
						$deviceTypesContainer['items'] = $deviceTypes;
					} 
					
				}
			}
			elseif (!$assemble)
			{
				$deviceTypesContainer['items'] = $deviceTypes;	
			}
		}
		
		return $deviceTypesContainer;		
	}
	
	/**
	 * (non-PHPdoc)
	 * @see FDWDeviceTypeServices::getDeviceTypes()
	 */
	public function getDeviceTypes($pageNumber=1, $pageSize=20)
	{
		return $this->findDeviceTypes($pageNumber, $pageSize, true);
	}

	/**
	 * (non-PHPdoc)
	 * @see FDWDeviceTypeServices::getDeviceType()
	 */
	public function getDeviceType($deviceTypeID)
	{
		$deviceType = null;
		if (isset($deviceTypeID)) 
		{
			$dt = $this->findDeviceTypeByID($deviceTypeID, 1);
			if ( isset($dt) && ($dt instanceof Lounge2_DeviceType) && (!$dt->is_empty_object())) 
			{
				$deviceType = $this->assembleDeviceType($dt);
			}
		}
		
		return $deviceType;		
	}
	
	/**
	 * (non-PHPdoc)
	 * @see FDWDeviceTypeServices::createDeviceType()
	 */
	public function createDeviceType($name = null, $devName = null, $isManageable = false, $macAddressPattern = null)
	{
		$deviceTypeCreated = false;
		if (isset($name) && isset($devName)) 
		{
			/**
			 * @var Lounge2_DeviceTypes
			 */
			$deviceTypes = null;
			$deviceTypesContainer = $this->findDeviceTypes(1, 2, false);
			$deviceTypes = $deviceTypesContainer['items'];
			if (isset($deviceTypes) && (!$deviceTypes->is_empty_object())) 
			{
				$responseCode = $deviceTypes->createDeviceType($name, $devName, $isManageable, $macAddressPattern);
				$deviceTypeCreated = ($responseCode == 201) ? true : false;
			}
		}
		
		return $deviceTypeCreated;
	} 
	
	/**
	 * @deprecated
	 * 
	 * Return a device type 
	 *   
	 * @param string $deviceType
	 * @param int $pageNumber
	 * 
	 * @return Lounge2_DeviceType
	 */
	protected function findDeviceTypeByName($deviceTypeName, $pageNumber=1)
	{
		$pageSize = 100;
		$startIndex = $this->getPagerStartIndex($pageNumber, $pageSize);
		/**
		 * @var Lounge2_DeviceTypes
		 */
		$deviceTypes = null;
		/**
		 * @var Lounge2_Devices
		 */
		$devices = null;
		/**
		 * @var Lounge2_DeviceType
		 */
		$foundDeviceType = null;
		
		$pager = null;
		
		if (isset($deviceTypeName)) 
		{
			/**
			 * Use cached versions of devices and device types resouce bundles if available
			 */
			if (!isset($this->deviceTypes)) 
			{
				if (!isset($this->devices)) 
				{
					if ($this->setUserDetails()) 
					{
						$devices = $this->flowCloud->admin_get_devices($startIndex, $pageSize);
						if ( isset($devices) && (!$devices->is_empty_object()) ) 
						{
							$deviceTypes = $devices->get_device_types($startIndex, $pageSize);
						}
					}
				}
				else
				{
					$deviceTypes = $this->devices->get_device_types();
				}
			}
			else
			{
				$deviceTypes = $this->deviceTypes;
			}

			
			if ( (isset($deviceTypes)) && (!$deviceTypes->is_empty_object()) ) 
			{
				$recordCount = $deviceTypes->count();
				$pager = $this->buildPagerMetadata($recordCount, $pageNumber, $pageSize);
				/**
				 * Search for the device Type
				 */
				foreach ($deviceTypes as $dt) 
				{
					if ($dt->Name == $deviceTypeName) 
					{
						$foundDeviceType = $dt;
						break;
					}
				}
				/**
				 * If the device was not found on this page, check if there are multiple
				 * pages and make a recursive call to this function to search the next page.
				 */
				if (!isset($foundDeviceType)) 
				{
					if ($pager['pagecount'] > $pageNumber) 
					{
						$this->findDeviceTypeByName($deviceTypeName, ($pageNumber + 1));
					}
				}
				/**
				 * cache the user's device types resource bundle if it all fits in one page 
				 */
				if ($pager['pagecount'] == 1) 
				{
					$this->deviceTypes = $deviceTypes;
				}				
			}
		}
		
		return $foundDeviceType;
	}
	
	/**
	 * Return a device type  matching the provided device type ID
	 *   
	 * @param string $deviceTypeID
	 * @param int $pageNumber
	 * 
	 * @return Lounge2_DeviceType
	 */
	protected function findDeviceTypeByID($deviceTypeID=null, $pageNumber=1)
	{
		$pageSize = 100;
		/**
		 * @var Lounge2_DeviceTypes
		 */
		$deviceTypes = null;
		/**
		 * @var Lounge2_DeviceType
		 */
		$foundDeviceType = null;
		$recordCount = 0;
		
		
		if (isset($deviceTypeID)) 
		{
			$deviceTypesContainer = $this->findDeviceTypes($pageNumber, $pageSize, false);
			$deviceTypes = $deviceTypesContainer['items'];
			
			if ( (isset($deviceTypes)) && ($deviceTypes instanceof Lounge2_DeviceTypes) && (!$deviceTypes->is_empty_object()) ) 
			{
				$recordCount = $deviceTypes->count();
				$pager = $this->buildPagerMetadata($recordCount, $pageNumber, $pageSize);
				if ($recordCount) 
				{
					/**
					 * Search for the device Type
					 */
					foreach ($deviceTypes as $dt) 
					{
						if ($dt->DeviceTypeID == $deviceTypeID) 
						{
							$foundDeviceType = $dt;
							break;
						}
					}
					
					/**
					 * If the device was not found on this page, check if there are multiple
					 * pages and make a recursive call to this function to search the next page.
					 */
					if (!isset($foundDeviceType)) 
					{
						if ($pager['pagecount'] > $pageNumber) 
						{
							$this->findDeviceTypeByID($deviceTypeID, ($pageNumber + 1));
						}
					}
				}
			}
		}
		
		return $foundDeviceType;
	}	
	
	/**
	 * Return an array representation of a device type
	 * 
	 * @param Lounge2_DeviceType $dt
	 * @return array
	 */
	protected function assembleDeviceType(Lounge2_DeviceType $dt)
	{
		$deviceType = null;
		if (isset($dt) && (!$dt->is_empty_object())) 
		{
			$isManagable = strtolower($dt->IsManageable);
			$im = ($isManagable == 'true') ? true : false;
			
			$deviceType = array(
				'DeviceTypeID' => $dt->DeviceTypeID,
				'Name' => $dt->Name,
				'DevName' => $dt->DevName,
				'IsManageable' => $im,
				'MACAddressPattern' => $dt->MACAddressPattern
			);
		}
		
		return $deviceType;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see FDWDeviceTypeServices::deleteDeviceTypeByID()
	 */
	public function deleteDeviceTypeByID($deviceTypeID = null)
	{
		$deleted = false;
		if (isset($deviceTypeID)) 
		{
			$deviceType = $this->findDeviceTypeByID($deviceTypeID, 1);
			if ( isset($deviceType) && ($deviceType instanceof Lounge2_DeviceType) && (!$deviceType->is_empty_object())) 
			{
				$deleted = $deviceType->delete();
			}			
		}
		return $deleted;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see FDWDeviceTypeServices::updateDeviceType()
	 */
	public function updateDeviceType($deviceTypeID = null, $name = null, $devName = null, $isManageable = false, $macAddressPattern = null)
	{
		$updated = false;
		if (isset($deviceTypeID)) 
		{
			$deviceType = $this->findDeviceTypeByID($deviceTypeID, 1);
			if ( isset($deviceType) && ($deviceType instanceof Lounge2_DeviceType) && (!$deviceType->is_empty_object())) 
			{
				$updated = $deviceType->updateDeviceType($name, $devName, $isManageable, $macAddressPattern);
			}			
		}
		return $updated;
	}
}