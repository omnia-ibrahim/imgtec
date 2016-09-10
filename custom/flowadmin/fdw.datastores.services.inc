<?php

/**
 * A collection of datastore management services available to tenant admins only
 * 
 * @author Joseph Eta <joseph.eta@imgtec.com>
 *
 */
interface FDWDatastoreServices
{
	/**
	 * Return a list of datastores to the tenant admin
	 * 
	 * The two dimentional returned array has the following keys: 
	 * 
	 * - items
	 * - pagecount
	 * 
	 * items is also an array with each item representing a datastore oject (also represented as an array ) with
	 * the following keys:
	 * 
	 * - Name
	 * - IsDeviceDataStore
	 * - IsUserDataStore
	 * 
	 * @param int $pageNumber
	 * @param int $pageSize
	 * 
	 * @return array
	 * 
	 * @throws FDWUnknownUserException
	 */
	public function getDatastores($pageNumber=1, $pageSize=20);
	
	/**
	 * Return the datastore with the supplied name
	 * 
	 * The returned array has the following keys:
	 * 
	 * - Name
	 * - IsDeviceDataStore
	 * - IsUserDataStore 
	 *  
	 * @param string $name
	 * 
	 * @return array 
	 * 
	 * @throws FDWUnknownUserException
	 * 
	 */
	public function getDatastore($name = null);
	
	/**
	 * Returns true if a new datastore was successfully created or false otherwise
	 * 
	 * @param string $name
	 * @param bool $isDeviceDatastore
	 * @param bool $isUserDatastore
	 * 
	 * @return boolean
	 * 
	 * @throws FDWUnknownUserException
	 */
	public function createDatastore($name=null, $isDeviceDatastore=true, $isUserDatastore=true);
	
	/**
	 * Return true if the datastore identified by the supplied name was successfully deleted or not
	 * 
	 * @param string $name
	 * @return bool
	 * 
	 * @throws FDWUnknownUserException
	 */
	public function deleteDatastore($name);
	
	
}