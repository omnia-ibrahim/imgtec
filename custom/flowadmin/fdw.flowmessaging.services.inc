<?php

/**
 * A collection of device type management services available to tenant admins only
 * 
 * @author Joseph Eta <joseph.eta@imgtec.com>
 *
 */
interface FDWFlowMessagingServices
{
	/**
	 * Return an array of flowmessaging topics. The array contains the following keys:
	 * 
	 *  - items => an array containing the actual topics
	 *  - pagecount => the page count based on the requested page size
	 *  - canCreate => is the user allowed to create new topics or not?
	 *  - limits => another multid dimentional array containing the following keys: 
	 *  	- MaxTopics
	 *  	- MaxAgeOriginal
	 *  	- MaxAgeParts => an array of maxAge parts broken down to Days, Hours, Minutes, Seconds
	 * 
	 * Each item in the items array represents a topic and is an array itself.
	 * Each topic array contains the following keys:
	 * 
	 * - Name
	 * - IsDeviceTopic
	 * - IsUserTopic
	 * - UseEventHistory
	 * - MaxAge
	 * 
	 * @param int $pageNumber
	 * @param int $pageSize
	 * 
	 * @return array
	 * 
	 * @throws FDWUnknownUserException
	 */
	public function getTopics($pageNumber=1, $pageSize=20);
	
	/**
	 * Return a FlowMessaging topic with the given name
	 * 
	 * The returned array has the following keys;
	 * 
	 * - Name
	 * - IsDeviceTopic
	 * - IsUserTopic
	 * - UseEventHistory
	 * - MaxAge
	 * 
	 * @param string $topicName
	 * 
	 * @return array
	 * 
	 * @throws FDWUnknownUserException 
	 */
	public function getTopic($topicName = null);
	
	/**
	 * Return the topic limits for this tenant in a multi dimentional array with the following keys:
	 * 
	 * - MaxTopics
	 * - MaxAgeOriginal
	 * - MaxAgeParts
	 * 
	 * @return array
	 * 
	 * @throws FDWUnknownUserException  
	 */
	public function getTopicLimits();
	
	/**
	 * Return true if a new topic was created or false otherwise
	 * 
	 * @param string $name
	 * @param bool $isDeviceTopic
	 * @param bool $isUserTopic
	 * @param bool $useEventHistory
	 * @param string $maxAge
	 * 
	 * @return bool
	 * 
	 * @throws FDWUnknownUserException 
	 */
	public function createTopic($name=null, $isDeviceTopic=true, $isUserTopic=true, $useEventHistory=true, $maxAge='06:00:00' );
	
	/**
	 * Returns true if the topic in questions was successfully updated or false otherwise
	 * 
	 * @param string $oldName
	 * @param string $name
	 * @param string $isDeviceTopic
	 * @param string $isUserTopic
	 * @param string $useEventHistory
	 * @param string $maxAge
	 * 
	 * @return bool
	 * 
	 * @throws FDWUnknownUserException 
	 */
	public function updateTopic($oldName=null, $name=null, $isDeviceTopic=true, $isUserTopic=true, $useEventHistory=true, $maxAge='06:00:00' );
	
	/**
	 * Returns true if the topic in question was deleted or false otherwise
	 * 
	 * @param string $name
	 */
	public function deleteTopicByName($name = null);
	
}