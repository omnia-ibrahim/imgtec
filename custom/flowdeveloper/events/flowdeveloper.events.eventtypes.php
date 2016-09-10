<?php

/**
 * Defines functions expected of all FLowdeveloper event types
 *  
 * @author Joseph Eta <joseph.eta@pure.com>
 */
interface  IFLDEventTypes
{
	const ACCOUNT_CREATED = 'AccountCreated';
	const ACCOUNT_UPDATED = 'AccountUpdated';
	const ACCOUNT_REMOVED = 'AccountRemoved';
}

/**
 * Defines response codes of the Flowdeveloper events management system
 * 
 * @author Joseph Eta <joseph.eta@pure.com>
 */
interface IFLDEventResponseCodes
{
	const OK = '200 OK';
	const CREATED = '201 Created';
	const BAD_REQUEST = '400 Bad request';
	const AUTHORIZATION_FAILED = '401 Authorization failed';
	const NOT_FOUND = '404 Not found';
	const METHOD_NOT_ALLOWED = '405 Method not allowed';
	const CONFLICT = '409 Conflict';
}

/**
 * Defines http content types expected from FLow
 * 
 * @author Joseph Eta <joseph.eta@pure.com>
 */
interface IFLDEventContentTypes
{
	const FLOW_EVENT = 'application/vnd.imgtec.com.events.xml';
}

/**
 * Defines the functions expected of every Flowdeveloper event
 * 
 * @author Joseph Eta <joseph.eta@pure.com>
 *
 */
interface IFLDEvent
{

	/**
	 * Returns the user local associated with the event
	 * @return string
	 */
	public function getCulture();
	
	/**
	 * Returns the event ID
	 * @return string
	 */
	public function getEventID();
	
	/**
	 * Return the name of the event type
	 * 
	 * @return String
	 */
	public function getEventType();
	
	/**
	 * Returns the licensee ID 
	 * @return int
	 */
	public function getLicenseeID();

	/**
	 * Returns the user ID
	 * @return string
	 */
	public function getUserID();

	/**
	 * Returns true if the event type is valid or false otherwise
	 * 
	 * @param String $eventType
	 * @return Boolean
	 */
	public function isValid($eventType);		
	
}

/**
 * Defines the functions expected of every Flowdeveloper account event
 * 
 * @author Joseph Eta <joseph.eta@pure.com>
 *
 */
interface IFLDAccountEvent
{
	/**
	 * Return the account email address
	 * @return String
	 */
	public function getEmailAddress();
	/**
	 * Return true if direct marketing messages can be sent to the account holder of false otherwise
	 * @return Boolean
	 */
	public function getAllowDirectMarketing();
	/**
	 * Return true if the account holder will like to receive direct email communication or false otherwise
	 * @return Boolean
	 */
	public function getAllowEmailCommunication();
	/**
	 * Return the account first name
	 * @return String
	 */
	public function getFirstName();	
	/**
	 * Return true if this account is activated or false otherwise
	 * @return Boolean
	 */
	public function getIsActivated();
	/**
	 * Return the account last name
	 * @return String
	 */
	public function getLastName();
	/**
	 * Returns the promotion/campaign name
	 * @return String
	 */
	public function getRefer();	
	/**
	 * Returns the promotion/campaign type
	 * @return String
	 */
	public function getReferType();	
	/**
	 * Returns the token associated with an change email request
	 * @return String
	 */
	public function getToken();
	/**
	 * Returns the token expiry date associated with a change email request
	 * @String
	 */
	public function getTokenExpires();	
}

/**
 * Defines functions expected of Flowdeveloper event handlers
 * 
 * @author Joseph Eta <joseph.eta@pure.com>
 */
interface IFLDEventHandler
{
	/**
	 * Process/handle the event
	 */
	public function execute();
	/**
	 * Update properties from supplied xml content
	 * 
	 * @param String $xmlPayload
	 */	
	public function loadProperties(DOMNode $xmlPayload);
}


/**
 * A base implementation of {@link IFLDEvent}
 * 
 * @author Joseph Eta <joseph.eta@pure.com>
 */
class FLDBaseEventImpl implements IFLDEvent
{
	protected $eventType = null;
	protected $eventID = null;
	protected $userID = null;
	protected $licenseeID = null;
	protected $culture = null;
	
	
	
	/**
	 * Create and initialize a new FLDEventType object
	 */		
	function __construct($name)
	{
		if ($this->isValid($name)) 
		{
			$this->eventType = $name;
		}
	}
	
	/**
	 * Yields all system resources currently reserved for this object 
	 */
	function __destruct()
	{
		unset($this->eventType);
	}	
		
	/**
	 * (non-PHPdoc)
	 * @see IFLDEvent::getEventType()
	 */
	public function getEventType()
	{
		return $this->eventType;
	}
	
	public function setEventType($eventType)
	{
	    $this->eventType = $eventType;
	}

	/**
	 * (non-PHPdoc)
	 * @see IFLDEvent::getEventID()
	 */
	public function getEventID()
	{
	    return $this->eventID;
	}

	public function setEventID($eventID)
	{
	    $this->eventID = $eventID;
	}

	/**
	 * (non-PHPdoc)
	 * @see IFLDEvent::getUserID()
	 */
	public function getUserID()
	{
	    return $this->userID;
	}

	public function setUserID($userID)
	{
	    $this->userID = $userID;
	}

	/**
	 * (non-PHPdoc)
	 * @see IFLDEvent::getLicenseeID()
	 */
	public function getLicenseeID()
	{
	    return $this->licenseeID;
	}

	public function setLicenseeID($licenseeID)
	{
	    $this->licenseeID = $licenseeID;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see IFLDEvent::getCulture()
	 */
	public function getCulture()
	{
	    return $this->culture;
	}

	public function setCulture($culture)
	{
	    $this->culture = $culture;
	}
	
	/**
	 * Validates the event type in question
	 * 
	 * @param String $eventType
	 */
	public function isValid($eventType)
	{
		$isValid = false;
		$eventTypes = array();
		$eventTypes[] = IFLDEventTypes::ACCOUNT_CREATED;
		$eventTypes[] = IFLDEventTypes::ACCOUNT_UPDATED;
		$eventTypes[] = IFLDEventTypes::ACCOUNT_REMOVED;		
		
		foreach ($eventTypes as $et) 
		{
			if ($eventType == $et) 
			{
				$isValid = true;
				break;
			}
		}
		
		return  $isValid;
	}		
}


/**
 * A base implementation of {@link IFLDAccountEvent}
 * 
 * @author Joseph Eta <joseph.eta@pure.com>
 *
 */
class FLDBaseAccountEventImpl extends FLDBaseEventImpl implements IFLDAccountEvent
{
	protected $emailAddress = null;
	protected $firstName = null;
	protected $lastName = null;
	protected $isActivated = false;
	protected $allowEmailCommunication = false;
	protected $allowDirectMarketing = false;
	protected $referType = null;
	protected $refer = null;
	protected $token = null;
	protected $tokenExpires = null;
	
	
	/**
	 * Create and initialize a new IFLDAccountEvent object
	 */		
	function __construct($name)
	{
		parent::__construct($name);
	}
	
	/**
	 * Yields all system resources currently reserved for this object 
	 */
	function __destruct()
	{
		parent::__destruct();
		unset($this->emailAddress);
		unset($this->firstName);
		unset($this->lastName);
		unset($this->isActivated);
		unset($this->allowDirectMarketing);
		unset($this->allowEmailCommunication);
		unset($this->refer);
		unset($this->referType);
		unset($this->token);
		unset($this->tokenExpires);											
	}

	
	/**
	 * (non-PHPdoc)
	 * @see IFLDAccountEvent::getEmailAddress()
	 */
	public function getEmailAddress()
	{
	    return $this->emailAddress;
	}

	public function setEmailAddress($emailAddress)
	{
	    $this->emailAddress = $emailAddress;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see IFLDAccountEvent::getFirstName()
	 */
	public function getFirstName()
	{
	    return $this->firstName;
	}

	public function setFirstName($firstName)
	{
	    $this->firstName = $firstName;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see IFLDAccountEvent::getLastName()
	 */
	public function getLastName()
	{
	    return $this->lastName;
	}

	public function setLastName($lastName)
	{
	    $this->lastName = $lastName;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see IFLDAccountEvent::getIsActivated()
	 */
	public function getIsActivated()
	{
	    return $this->isActivated;
	}

	public function setIsActivated($isActivated)
	{
		
	    $this->isActivated = (strtolower($isActivated) == 'true') ? true : false;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see IFLDAccountEvent::getAllowEmailCommunication()
	 */
	public function getAllowEmailCommunication()
	{
	    return $this->allowEmailCommunication;
	}

	public function setAllowEmailCommunication($allowEmailCommunication)
	{
	    $this->allowEmailCommunication = (strtolower($allowEmailCommunication) == 'true') ? true : false;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see IFLDAccountEvent::getAllowDirectMarketing()
	 */
	public function getAllowDirectMarketing()
	{
	    return $this->allowDirectMarketing;
	}

	public function setAllowDirectMarketing($allowDirectMarketing)
	{
	    $this->allowDirectMarketing = (strtolower($allowDirectMarketing) == 'true') ? true : false;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see IFLDAccountEvent::getReferType()
	 */
	public function getReferType()
	{
	    return $this->referType;
	}

	public function setReferType($referType)
	{
	    $this->referType = $referType;
	}

	/**
	 * (non-PHPdoc)
	 * @see IFLDAccountEvent::getRefer()
	 */
	public function getRefer()
	{
	    return $this->refer;
	}

	public function setRefer($refer)
	{
	    $this->refer = $refer;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see IFLDAccountEvent::getToken()
	 */
	public function getToken()
	{
	    return $this->token;
	}

	public function setToken($token)
	{
	    $this->token = $token;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see IFLDAccountEvent::getTokenExpires()
	 */
	public function getTokenExpires()
	{
	    return $this->tokenExpires;
	}

	public function setTokenExpires($tokenExpires)
	{
	    $this->tokenExpires = $tokenExpires;
	}
	
	protected function loadBaseProperties(DOMNode $xmlPayload)
	{
		$propertiesLoaded = false;
		if (isset($xmlPayload) && $xmlPayload->hasChildNodes()) 
		{
			/**
			 * Defines object properties names as expected in XML payload and their corresponding setter methods
			 * on the account event object 
			 */
			$propertyMap = array(
				'EventID' => 'setEventID',
				'UserID' => 'setUserID',
				'LicenseeID' => 'setLicenseeID',
				'Culture' => 'setCulture',
				'EmailAddress' => 'setEmailAddress',
				'FirstName' => 'setFirstName',
				'LastName' => 'setLastName',
				'IsActivated' => 'setIsActivated',
				'AllowEmailCommunication' => 'setAllowEmailCommunication',
				'AllowDirectMarketing' => 'setAllowDirectMarketing',
				'ReferType' => 'setReferType',
				'Refer' => 'setRefer',
				'Token' => 'setToken',
				'TokenExpires' => 'setTokenExpires'
				
			);
	
			//$propertyList = array_keys($propertyMap);
			
			foreach ($xmlPayload->childNodes as $node) 
			{
				$nname = $node->nodeName;
				//_flowautho_debug('[FLDBaseAccountEventImpl::loadBaseProperties] Processing Node: '. $nname);
				if ($nname == 'Properties') 
				{
					if ($node->hasChildNodes()) 
					{
						foreach ($node->childNodes as $propNode) 
						{
							if ($propNode->nodeName == 'Property') 
							{
								$this->loadProperty($propNode, $propertyMap);
							}
						}
					}
					
				}
				elseif (array_key_exists($nname, $propertyMap))
				{
					$setterName = $propertyMap[$nname];
					$this->$setterName($node->nodeValue);
					//_flowautho_debug('[FLDBaseAccountEventImpl::loadBaseProperties] Setting Property::' . $nname . ', SetterMethod:: '. $setterName . ', Value::'. $node->nodeValue);
				}
			}
			$propertiesLoaded = true;
			
		}
		
		return $propertiesLoaded;
	}
	
	private function loadProperty(DOMNode $propertyNode, array $propertyMap)
	{
		$propertyLoaded = false;
		$keyList = $propertyNode->getElementsByTagName('Key');
		if ($keyList && $keyList->length) 
		{
			$keyNode = $keyList->item(0);
			$key = $keyNode->nodeValue;
			if (array_key_exists($key, $propertyMap)) 
			{
				$setterName = $propertyMap[$key];
				$valueList = $propertyNode->getElementsByTagName('Value');
				if ($valueList && $valueList->length) 
				{
					$valueNode = $valueList->item(0);
					$this->$setterName($valueNode->nodeValue);
					$propertyLoaded = true;
					//_flowautho_debug('[FLDBaseAccountEventImpl::loadProperty] Setting Property::' . $key . ', SetterMethod:: '. $setterName . ', Value::'. $valueNode->nodeValue);
				}
			}
		}
		
		return $propertyLoaded;
	}
}


/**
 * Implemenation of the "AccountCreatedEvent" event and its handler
 * 
 * @author Joseph Eta <joseph.eta@pure.com>
 */
class FLDAccountCreatedEvent extends FLDBaseAccountEventImpl implements IFLDEventHandler
{
	function __construct()
	{
		parent::__construct(IFLDEventTypes::ACCOUNT_CREATED);
	}
	
	function __destruct()
	{
		parent::__destruct();
	}
	
	public function execute()
	{
		//_flowautho_debug('[FLDAccountCreatedEvent::execute] UserID: '. $this->getUserID() . ', Email: '.$this->getEmailAddress() . ', LicenseeID: '. $this->getLicenseeID());
		
		$email = $this->getEmailAddress();
		$userID = $this->getUserID();
		$user = user_load(array('mail' => $email));
		if ($user && ($user->status == '1')) 
		{
			//_flowautho_debug('[FLDAccountCreatedEvent::execute] DrupalUser-ACTIVATED: '. print_r($user, true));
		}
		elseif ($user && ($user->status == '0'))
		{
			if ($this->getIsActivated()) 
			{
				$account['status'] = 1;
				$user = user_save($user, $account);
				//_flowautho_debug('[FLDAccountCreatedEvent::execute] Drupal User-NOT-ACTIVATED: '. print_r($user, true));
			}
			
		}
		elseif (!$user)
		{
			$account['mail'] = $email;
			$account['pass'] = FLOWDEVEL_DEFAULT_PWORD;
			$account['name'] = $email;
			$account['init'] = $userID;
			$account['lounge2_guid'] = $userID;			
			$account['licensee_id'] = $this->getLicenseeID();
			
			if ($this->getIsActivated()) 
			{
				$account['status'] = 1;
			}
			else
			{
				$account['status'] = 0;
			} 
			
			$newUser = user_save(null, $account); // save new user	
			//_flowautho_debug('[FLDAccountCreatedEvent::execute] Drupal NEW USER: '. print_r($newUser, true));

			if ($newUser) 
			{
				if (function_exists('flowuser_add_user')) 
			    {
					$flowuser['auth_token'] = ''; 
					$flowuser['auth_token_expiry'] = '';
					$flowuser['session_token'] = ''; 
					$flowuser['session_token_expiry'] = '';  
					$flowuser['uid'] = $newUser->uid; 
					$flowuser['guid'] = $userID;
					$flowuser['licensee_id'] = $this->getLicenseeID(); 
					flowuser_add_user($flowuser);
			    }  
			}
			
	    			
		}

		
	}
	
	public function loadProperties(DOMNode $xmlPayload)
	{
		$propertiesLoaded = $this->loadBaseProperties($xmlPayload);
		
		return $propertiesLoaded;
	}
	
	
}

/**
 * Implemenation of the "AccountUpdatedEvent" event and its handler
 * 
 * @author Joseph Eta <joseph.eta@pure.com>
 */
class FLDAccountUpdatedEvent extends FLDBaseAccountEventImpl implements IFLDEventHandler
{
	function __construct()
	{
		parent::__construct(IFLDEventTypes::ACCOUNT_UPDATED);
	}
	
	function __destruct()
	{
		parent::__destruct();
	}

	public function execute()
	{
		$user = flowuser_find_user_by_guid($this->getUserID());
		$account['mail'] = $this->getEmailAddress();
		$userToUpdate = user_load(array('uid' => $user['uid']));
		//_flowautho_debug('[FLDAccountUpdatedEvent::execute] UserID: '. $this->getUserID() . ', Email: '.$this->getEmailAddress());		
		//_flowautho_debug('[FLDAccountUpdatedEvent::execute] User: '. print_r($user, true));
		//_flowautho_debug('[FLDAccountUpdatedEvent::execute] InfoToUpdate: '. print_r($account, true));				
		//_flowautho_debug('[FLDAccountUpdatedEvent::execute] AccountToUpdate: '. print_r($userToUpdate, true));
				
		if ($userToUpdate) 
		{
			$updatedUser = user_save($userToUpdate, $account);
		}
	}
	
	public function loadProperties(DOMNode $xmlPayload)
	{
		$propertiesLoaded = $this->loadBaseProperties($xmlPayload);
		
		return $propertiesLoaded;
	}
}

/**
 * Implemenation of the "AccountRemovedEvent" event and its handler
 * 
 * @author Joseph Eta <joseph.eta@pure.com>
 */
class FLDAccountRemovedEvent extends FLDBaseAccountEventImpl implements IFLDEventHandler
{
	function __construct()
	{
		parent::__construct(IFLDEventTypes::ACCOUNT_REMOVED);
	}
	
	function __destruct()  
	{
		parent::__destruct();
	}

	public function execute()
	{
		$user = flowautho_get_user_data_by_email($this->getEmailAddress());
		//_flowautho_debug('[FLDAccountRemovedEvent::execute] UserID: '. $this->getUserID() . ', Email: '.$this->getEmailAddress());
		//_flowautho_debug('[FLDAccountRemovedEvent::execute] User: '. print_r($user, true));
		if ($user && is_array($user)) 
		{
			user_delete($user['uid']);
			flowuser_delete_user($user['uid'], $user['data']['lounge2_guid']);
		}
	}
	
	public function loadProperties(DOMNode $xmlPayload)
	{
		$propertiesLoaded = $this->loadBaseProperties($xmlPayload);
		
		return $propertiesLoaded;
	}
}

/**
 * Manages the instantiation of Flowdeveloper events
 * 
 * @author Joseph Eta <joseph.eta@pure.com>
 *
 */
class FLDEventFactory
{
	private static $eventTypeMap = array(
	
		IFLDEventTypes::ACCOUNT_CREATED => 'FLDAccountCreatedEvent',
		IFLDEventTypes::ACCOUNT_UPDATED => 'FLDAccountUpdatedEvent',
		IFLDEventTypes::ACCOUNT_REMOVED => 'FLDAccountRemovedEvent'
	);
	
	/**
	 * Return a new instance of the supplied event type
	 * 
	 * @param unknown_type $eventType
	 * @return FLDBaseEventImpl
 	 * @throws FLDIllegalEventException if the the supplied event type is unknown
	 */
	public static function create($eventType)
	{
		$newObject = null;
		$errorMsg = 'The supplied event type:: '. $eventType.' is unknown';
		if (isset(self::$eventTypeMap[$eventType])) 
		{
			$objectClass = self::$eventTypeMap[$eventType];
			if (class_exists($objectClass)) 
			{
				$newObject = new $objectClass($eventType);
			}
			else
			{
				throw new FLDIllegalEventException($errorMsg);	
			}
		}
		else
		{
			throw new FLDIllegalEventException($errorMsg);
		}
		
		return $newObject;
		
	}
}

/**
 * Represents a an unknow event exception
 * 
 * @author Joseph Eta <joseph.eta@pure.com>
 *
 */
class FLDIllegalEventException extends Exception
{
	/**
	 * Instantiates a new FLDIllegalEventException
	 * 
	 * @param String $errorMsg
	 * @param String $errorCode
	 */
	function __construct($errorMsg, $errorCode=0)
	{
		parent::__construct($errorMsg, $errorCode);
	}
}

class FLDEventsManager
{
	private $eventsRepository = null;
	private $listNodeQuery = '/Events';
	private $listItemNodeName = 'Event';
	
	
	public function __construct()
	{
		$this->eventsRepository = array();
	}
	
	public function __destruct()
	{
		unset($this->eventsRepository);
	}

	public function loadXML($xmlPayload)
	{
		$responseCode = IFLDEventResponseCodes::OK;
		return $responseCode;
		//_flowautho_debug('[FLDEventsManager::loadXML] XML Payload: '. print_r($xmlPayload));
	}
	
	public function processEvents(DOMDocument $xmlPayload)
	{
		$responseCode = IFLDEventResponseCodes::OK;
		if (isset($xmlPayload)) 
		{

			$eventsNode = $xmlPayload->documentElement;
			foreach ($eventsNode->childNodes as $node) 
			{
				if ($node->nodeName == 'Event') 
				{
					$eventTypeNode = $node->getElementsByTagName('EventType');
					if ($eventTypeNode && $eventTypeNode->length) 
					{
						$eventType = $eventTypeNode->item(0)->nodeValue;
						try {
								$eventObject = FLDEventFactory::create($eventType);
								//_flowautho_debug('[FLDEventsManager::processEvents] Node Name: '. $node->nodeName . ', EventType: '. $eventType . ', EventObjectClass: '. get_class($eventObject));
								if ($eventObject instanceof IFLDEventHandler) 
								{
									if ($eventObject->loadProperties($node)) 
									{
										$this->eventsRepository[] = $eventObject;
									}
								}
																	
						} catch (FLDIllegalEventException $e) {
							
							watchdog('Flowdevel', 'Failed to create Flow event object of event type: '. $eventType);
							$responseCode = IFLDEventResponseCodes::BAD_REQUEST;
							break;
						}
						
					}
				}
			}
			
			if (count($this->eventsRepository)) 
			{
				foreach ($this->eventsRepository as $eo) 
				{
					if ($eo instanceof IFLDEventHandler) 
					{
						$eo->execute();
					}
				}
			}
		}
		
		return $responseCode;
	}
	
}
