<?php


class FDWFlowMessagingServicesImpl extends FDWFlowCloudClientImpl implements FDWFlowMessagingServices
{
	/**
	 * @var Lounge2_Service
	 */
	protected $flowmessaging = null;
	
	/**
	 * This property will be populated only if all flowmessaging topics were returned in a single page.
	 * So this is highly dependent on the page size specified when the call was made
	 *  
	 * @var Lounge2_Topics
	 */
	protected  $topics = null;	
	
	/**
	 * Create an instance of FDWFlowMessagingServicesImpl and initialize the flowCloud variable
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
	 * (non-PHPdoc)
	 * @see FDWFlowMessagingServices::getTopics()
	 */
	public function getTopics($pageNumber=1, $pageSize=20)
	{
		$assembledTopics = array('items' => array(), 'pagecount' => 0, 'limits' => array(), 'canCreate' => false);
		$topicsContainer = $this->findTopics($pageNumber, $pageSize);
		$topics = $topicsContainer['items'];
		if (isset($topics) && ($topics instanceof Lounge2_Topics) && (!$topics->is_empty_object())) 
		{
			foreach ($topics as $topic) 
			{
				$assembledTopics['items'][] = $this->assembleTopic($topic);
			}
			$assembledTopics['pagecount'] = $topicsContainer['pagecount'];	
			
			/**
			 * @var Lounge2_TopicLimit
			 */
			$topicLimit = null;
			$topicLimit = $topics->getTopicLimits();
			if (isset($topicLimit) && ($topicLimit instanceof Lounge2_TopicLimit) && (!$topicLimit->is_empty_object())) 
			{
				$assembledTopicLimits = $this->assembleTopicLimits($topicLimit);
				$assembledTopics['limits'] = $assembledTopicLimits;
			}
			
			$assembledTopics['canCreate'] = $topics->canCreateTopic();
		}
		
		return $assembledTopics;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see FDWFlowMessagingServices::getTopic()
	 */
	public function getTopic($topicName = null)
	{
		$topic = null;
		if (isset($topicName)) 
		{
			$foundTopic = $this->findTopicByName($topicName, 1);
			if ( isset($foundTopic) && ($foundTopic instanceof Lounge2_Topic) && (!$foundTopic->is_empty_object())) 
			{
				$topic = $this->assembleTopic($foundTopic);
			}
		}
		
		return $topic;			
	}

	/**
	 * (non-PHPdoc)
	 * @see FDWFlowMessagingServices::getTopicLimits()
	 */
	public function getTopicLimits()
	{
		$assembledTopicLimits = null;
		
		if (!isset($this->topics)) 
		{
			/**
			 * It the topics variable has not been set it means we are not dealing with a 
			 * topics list so we can request a single topic from the topic list just to get to
			 * the limits REL LINK.
			 */
			$topicsContainer = $this->findTopics(1, 1);
			$topics = $topicsContainer['items'];
		}
		else
		{
			$topics = $this->topics;
		}
		
		if (isset($topics) && ($topics instanceof Lounge2_Topics) && (!$topics->is_empty_object())) 
		{
			/**
			 * @var Lounge2_TopicLimit
			 */
			$topicLimit = null;
			$topicLimit = $topics->getTopicLimits();
			if (isset($topicLimit) && ($topicLimit instanceof Lounge2_TopicLimit) && (!$topicLimit->is_empty_object())) 
			{
				$assembledTopicLimits = $this->assembleTopicLimits($topicLimit);
			}
		}
		
		return $assembledTopicLimits;
	}

	/**
	 * (non-PHPdoc)
	 * @see FDWFlowMessagingServices::createTopic()
	 */
	public function createTopic($name=null, $isDeviceTopic=true, $isUserTopic=true, $useEventHistory=true, $maxAge='06:00:00' )
	{
		$topicCreated = false;
		if (!isset($this->topics)) 
		{
			/**
			 * It the topics variable has not been set it means we are not dealing with a 
			 * topics list so we can request a single topic from the topic list just to get to
			 * the "add" REL LINK.
			 */
			$topicsContainer = $this->findTopics(1, 1);
			$topics = $topicsContainer['items'];
		}
		else
		{
			$topics = $this->topics;
		}
		
		if (isset($topics) && ($topics instanceof Lounge2_Topics) && (!$topics->is_empty_object())) 
		{
			if ($topics->canCreateTopic()) 
			{
				if ($topics->createTopic($name, $isDeviceTopic, $isUserTopic, $useEventHistory, $maxAge) == FDWFlowCloudClient::RESOURCE_CREATED) 
				{
					$topicCreated = true;
				}
			}
		}
				
		return $topicCreated;
	}
	
	/**
	 * (non-PHPdoc)
	 * @see FDWFlowMessagingServices::updateTopic()
	 */
	public function updateTopic($oldName=null, $name=null, $isDeviceTopic=true, $isUserTopic=true, $useEventHistory=true, $maxAge='06:00:00')
	{
		$updated = false;
		if (isset($name)) 
		{
			$foundTopic = $this->findTopicByName($oldName, 1);
			if ( isset($foundTopic) && ($foundTopic instanceof Lounge2_Topic) && (!$foundTopic->is_empty_object())) 
			{
				$updated = $foundTopic->updateTopic($name, $isDeviceTopic, $isUserTopic, $useEventHistory, $maxAge);
			}
		}
		
		return $updated;			
	}
	
	/**
	 * (non-PHPdoc)
	 * @see FDWFlowMessagingServices::deleteTopicByName()
	 */
	public function deleteTopicByName($name = null)
	{
		$deleted = false;
		if (isset($name)) 
		{
			$foundTopic = $this->findTopicByName($name, 1);
			if ( isset($foundTopic) && ($foundTopic instanceof Lounge2_Topic) && (!$foundTopic->is_empty_object())) 
			{
				$deleted = $foundTopic->delete();
			}
		}
		
		return $deleted;			
	}
	
	/**
	 * Retrieved a paged list of topics.
	 * 
	 * @param int $pageNumber
	 * @param int $pageSize
	 * @param int $assemble
	 */
	protected function findTopics($pageNumber=1, $pageSize=20)
	{
		$topicsContainer = array('items' => array(), 'pagecount' => 0);
		
		if (isset($pageNumber) && isset($pageSize)) 
		{
			$startIndex = $this->getPagerStartIndex($pageNumber, $pageSize);
			/**
			 * @var Lounge2_Topics
			 */
			$topics = null;
			$pager = null;
			$recordCount = 0;

			if (!isset($this->topics)) 
			{
				$topics = $this->flowCloud->admin_get_topics($startIndex, $pageSize);
			}
			else
			{
				$topics = $this->topics;
			}

			if (isset($topics) && (!$topics->is_empty_object())) 
			{
				$recordCount = $topics->count();
				if ($recordCount) 
				{
					$pager = $this->buildPagerMetadata($recordCount, $pageNumber, $pageSize);
					$topicsContainer['pagecount'] = $pager['pagecount'];
					/**
					 * cache the topics list if it all fits in one page 
					 */			
					if ($pager['pagecount'] == 1) 
					{
						$this->topics = $topics;
					}
					
					//$topicsContainer['items'] = $topics;
				}
				
				$topicsContainer['items'] = $topics;
			}
		}
		
		return $topicsContainer;		
	}
	
	/**
	 * Return the FlowMessaging topic with the specified name
	 * 
	 * @param string $topicName
	 * @param int $pageNumber
	 */
	protected function findTopicByName($topicName=null, $pageNumber = 1)
	{
		$pageSize = 100;
		/**
		 * @var Lounge2_Topics
		 */
		$topics = null;
		/**
		 * @var Lounge2_Topic
		 */
		$foundTopic = null;
		$recordCount = 0;

		if (isset($topicName)) 
		{
			if (!isset($this->topics)) 
			{
				$topicsContainer = $this->findTopics($pageNumber, $pageSize);
				$topics = $topicsContainer['items'];
				if (isset($topics) && ($topics instanceof Lounge2_Topics) && (!$topics->is_empty_object())) 
				{
					$recordCount = $topics->count();
					$pager = $this->buildPagerMetadata($recordCount, $pageNumber, $pageSize);
					if ($recordCount) 
					{
						/**
						 * Search for the topic
						 */
						foreach ($topics as $topic) 
						{
							if ($topic->Name == $topicName) 
							{
								$foundTopic = $topic;
								break;
							}
						}
						
						/**
						 * If the topic was not found on this page, check if there are multiple
						 * pages and make a recursive call to this function to search the next page.
						 */
						if (!isset($foundTopic)) 
						{
							if ($pager['pagecount'] > $pageNumber) 
							{
								$this->findTopicByName($topicName, ($pageNumber + 1));
							}
						}						
					}
				}
			}
			else
			{
				$topics = $this->topics;
			}
		}
		
		return $foundTopic;
	}

	/**
	 * Return an array representation of a Lounge2_Topic
	 * 
	 * @param Lounge2_Topic $topic
	 * 
	 */
	protected function assembleTopic(Lounge2_Topic $topic)
	{
		$assembledTopic = null;
		if (isset($topic) && (!$topic->is_empty_object())) 
		{
			$isDT = (strtolower($topic->IsDeviceTopic) == 'true') ? true : false;
			$isUT = (strtolower($topic->IsUserTopic) == 'true') ? true : false;
			$userEH = (strtolower($topic->UseEventHistory) == 'true') ? true : false;
			
			
			
			$assembledTopic = array(
				'Name' => $topic->Name,
				'IsDeviceTopic' => $isDT,
				'IsUserTopic' => $isUT,
				'UseEventHistory' => $userEH,
				'MaxAge' => $topic->MaxAge,
				'MaxSizeBytes' => @$topic->MaxSizeBytes,
				'CanUpdate' => $topic->canUpdate(),
				'CanDelete' => $topic->canDelete()	
					
			);
		}
		
		return $assembledTopic;		
	}
	
	/**
	 * Return and array representation of a Topic Limit object
	 * 
	 * @param Lounge2_TopicLimit $topicLimit
	 * @return array
	 */
	protected function assembleTopicLimits(Lounge2_TopicLimit $topicLimit)
	{
		$assembledTopicLimit = array();
		if (isset($topicLimit)) 
		{
			$maxAgeParts = explode(':', $topicLimit->MaxAge);
			$daysHours = explode('.', $maxAgeParts[0]);
			$days = 0;
			$hours  = 6;
			
			if (count($daysHours) == 2) 
			{
				$days = $daysHours[0];
				$hours = $daysHours[1];
			}
			elseif (count($daysHours) == 1)
			{
				$hours = $daysHours[0];
			}
			
			$assembledTopicLimit['MaxTopics'] = $topicLimit->MaxTopics;
			$assembledTopicLimit['MaxAgeOriginal'] = $topicLimit->MaxAge;
			$assembledTopicLimit['MaxAgeParts'] = array('Days' => $days, 'Hours' => $hours, 'Minutes' => $maxAgeParts[1], 'Seconds' => $maxAgeParts[2]);
			
		}
		return $assembledTopicLimit;
	}
}