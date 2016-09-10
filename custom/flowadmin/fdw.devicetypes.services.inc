<?php

/**
 * A collection of device type management services available to tenant admins only
 * 
 * @author Joseph Eta <joseph.eta@imgtec.com>
 *
 */
interface FDWDeviceTypeServices
{
	/**
	 * Return an array of device types. Each item in the array represents a device type and is an array itself.
	 * 
	 * Each device type array contains the following keys:
	 * 
	 * - DeviceTypeID
	 * - Name
	 * - DevName
	 * - IsManageable
	 * - MACAddressPattern
	 * 
	 * @param int $pageNumber
	 * @param int $pageSize
	 * 
	 * @return array
	 * 
	 * @throws FDWUnknownUserException
	 */
	public function getDeviceTypes($pageNumber=1, $pageSize=20);
	
	/**
	 * Returns the device type identified by the supplied ID
	 * 
	 * The device type will be represented by an associative array with the following keys
	 * 
	 * - DeviceTypeID
	 * - Name
	 * - DevName
	 * - IsManageable
	 * - MACAddressPattern
	 * 
	 * @param string $deviceTypeID
	 * @return array
	 * 
	 * @throws FDWUnknownUserException
	 */
	public function getDeviceType($deviceTypeID);

	/**
	 * Returns true if a new device type was successfully created or false otherwise
	 *  
	 * @param string $name
	 * @param string $devName
	 * @param boolean $isManageable
	 * @param string $macAddressPattern
	 * @return boolean 
	 * 
	 * @throws FDWUnknownUserException
	 */
	public function createDeviceType($name = null, $devName = null, $isManageable = false, $macAddressPattern = null);
	
	/**
	 * Returns true if the device type with the supplied ID was deleted or false other wise
	 * 
	 * @param string $deviceTypeID
	 * @return boolean
	 * 
	 * @throws FDWUnknownUserException
	 */
	public function deleteDeviceTypeByID($deviceTypeID = null);
	
	/**
	 * Returns true if a new device type was successfully updated or false otherwise
	 *  
	 * @param string $name
	 * @param string $devName
	 * @param boolean $isManageable
	 * @param string $macAddressPattern
	 * @return boolean 
	 * 
	 * @throws FDWUnknownUserException
	 */	
	public function updateDeviceType($deviceTypeID = null, $name = null, $devName = null, $isManageable = false, $macAddressPattern = null);
	
	
}