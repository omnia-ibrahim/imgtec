<?php

define('FLOWADMIN_TOPICS', 'topics');
define('FLOWADMIN_UPGRADE', 'upgrade');

/**
 * Return a list of device types related menu paths
 * Enter description here ...
 */
function _flowadmin_menu_topics()
{
	$items = array();
	
	$items[FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_TOPICS.'/%'] = array(
		'title' => t('FlowMessaging Topics'),
		'description' => t('FlowMessaging Topic list'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowadmin_generate_topics_page',
		'page arguments' => array(3),
		'type' => MENU_NORMAL_ITEM,
		'weight' => 51,
	);
	
	
	$items[FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_TOPICS.'/'.FLOWADMIN_ADD] = array(
		'title' => t('Add a FlowMessaging Topic'),
		'description' => t('Add a FlowMessaging Topic to a particular tenant'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowadmin_generate_add_topic_page',
		'page arguments' => array(NULL),
		'type' => MENU_NORMAL_ITEM,
		'weight' => 51,
	);	
	
	$items[FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_TOPICS.'/%/'.FLOWADMIN_EDIT] = array(
		'title' => t('Edit FlowMessaging Topic'),
		'description' => t('Edit and existing FlowMessaging Topic specification'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowadmin_generate_add_topic_page',
		'page arguments' => array(3),
		'type' => MENU_NORMAL_ITEM,
		'weight' => 51,
	);

	
	$items[FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_TOPICS.'/'.FLOWADMIN_UPGRADE] = array(
		'title' => t('FlowMessaging Topics Upgrade Message'),
		'description' => t('Call to action to upgrade inorder to be able to create more FlowMessaging Topics'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowadmin_generate_topic_limits_page',
		'type' => MENU_NORMAL_ITEM,
		'weight' => 51,
	);

	
	$items[FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_TOPICS.'/%/'.FLOWADMIN_DELETE] = array(
		'title' => t('Delete FlowMessaging Topic'),
		'description' => t('Delete A FlowMessaging Topic'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowadmin_delete_topic',
		'page arguments' => array(3),	
		'type' => MENU_NORMAL_ITEM,
		'weight' => 50,
	);		

	return $items;
}


function _flowadmin_theme_topics()
{
	$items = array(
	
		'flowadmin_topics_headerright'  => array(
			'variables' => array('url' => NULL),
			'template' => 'flowadmin.topics.headerright',
			'path' => drupal_get_path('module', 'flowadmin') . "/themes",
		),	

		'flowadmin_topics_maincontent'  => array(
			'variables' => array('topics' => NULL, 'pageCount' => NULL, 'pageNumber' => NULL),
			'template' => 'flowadmin.topics.maincontent',
			'path' => drupal_get_path('module', 'flowadmin') . "/themes",
		),

		'flowadmin_topics_btn_panel'  => array(
			'variables' => array('topic' => NULL),
			'template' => 'flowadmin.topics.btn_panel',
			'path' => drupal_get_path('module', 'flowadmin') . "/themes",
		),	
	
	);
	
	return $items;
}


function flowadmin_generate_topics_page()
{
	global $user;
	$htmlOutput = null;
	
	flowadmin_access();
	
	try {
			$pageNumber = func_get_arg(0);
			$pageNumber = (isset($pageNumber)) ? $pageNumber : 1;
			$pageSize = 10;
			$oauthInfo = flowautho_get_oauth_credentials($user->mail);
			$flowMessagingServices = new FDWFlowMessagingServicesImpl($oauthInfo, $user);
			$topicsContainer = $flowMessagingServices->getTopics($pageNumber, $pageSize);
			$topics = $topicsContainer['items'];
			
			//drupal_set_message('<pre>[flowadmin_generate_topics_page:: ] Topics:: '. print_r($topicsContainer, true).'</pre>');
			if ($topicsContainer['canCreate']) 
			{
				$addURL = base_path() . FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_TOPICS.'/'.FLOWADMIN_ADD;
			}
			else
			{
				$addURL = base_path() . FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_TOPICS.'/'.FLOWADMIN_UPGRADE;
			}
			
			
			$headerLeft = '';
			$headerRight = theme('flowadmin_topics_headerright', array('url' => $addURL));
			$contentArgs =  array('topics' => $topics, 'pageCount' => $topicsContainer['pagecount'], 'pageNumber' => $pageNumber);
			$mainContent = theme('flowadmin_topics_maincontent', $contentArgs);
				
			$htmlOutput =  theme('flowautho_dashboard_content', array('headerLeft' => $headerLeft, 
													  'headerCenter' => t('FlowMessaging Topics'),  
													  'headerRight' => $headerRight, 
													  'mainContent' => $mainContent));	
					
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWFlowMessagingServicesImpl error:: '. print_r($e->getMessage(),true));
	}
	
	return $htmlOutput;
}

function flowadmin_generate_add_topic_page()
{
	global $user;
	$htmlOutput = null;
	
	flowadmin_access();
		
	$topicName = func_get_arg(0);
	$topicForm = drupal_get_form('flowadmin_topic_form', $topicName);
	
	$headerLeft = '';
	$headerRight = '';
	$mainContent = drupal_render($topicForm);
	$pageTitle = (isset($topicName)) ? t('Edit FlowMessaging Topic') : t('Add FlowMessaging Topic') ;
		
	$htmlOutput =  theme('flowautho_dashboard_content', array('headerLeft' => $headerLeft, 
											  'headerCenter' => $pageTitle,  
											  'headerRight' => $headerRight, 
											  'mainContent' => $mainContent));
		
	return $htmlOutput;	
}


function flowadmin_topic_form($form, &$form_state, $topicName=null)
{
	global $user;
	$topic = null;
	$form = array();
	
	try {
		
		$oauthInfo = flowautho_get_oauth_credentials($user->mail);
		$flowMessagingServices = new FDWFlowMessagingServicesImpl($oauthInfo, $user);			
		if (isset($topicName)) 
		{
			$topic = $flowMessagingServices->getTopic($topicName);
			$topic['formattedMaxAge'] = _flowadmin_convert_maxage_string_to_minutes($topic['MaxAge']);
			//drupal_set_message('<pre>[flowadmin_topic_form::] MaxAge:: '. print_r($topic['MaxAge'], true).'</pre>');
		}
		
		$topicLimits = $flowMessagingServices->getTopicLimits();
		
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWFlowMessagingServicesImpl error:: '. print_r($e->getMessage(),true));
	}
	
	if (!isset($topic)) 
	{
		$topic = array('Name'=>'', 'IsDeviceTopic'=>true, 'IsUserTopic'=>true, 'UseEventHistory'=>true,'MaxAge'=>'', 'formattedMaxAge'=>'');
	}
	
	
	//drupal_set_message('<pre>[flowadmin_topic_form::] Limits:: '. print_r($topicLimits, true) .'</pre>');
	
	$form['old_topic_name'] = array(
		'#type' => 'hidden',
		'#value' => $topicName,
	);
	
	$form['maxage_limits'] = array(
		'#type' => 'hidden',
		'#value' => implode('-', $topicLimits['MaxAgeParts']),
	);	

	$form['name'] = array(
	  '#type' => 'textfield', 
	  '#title' => 'Name',
	  '#description' => t('Only a-z, A-Z, 0123456789, "_" and "-" are allowed and no more than 50 characters.'),	
	  '#maxlength' => 50,
	  '#required' => TRUE,
	  '#attributes' => array('class' => array('c-ate-topic-form-name')),
	  '#default_value' => $topic['Name'], 
	 
	);	
	
	$form['isdevicetopic'] = array(
	   '#type' => 'checkbox', 
	   '#title' => 'Is a Device topic',
	   '#description' => t('User owned devices will be able to subscribe to this topic'),	
	   '#attributes' => array('class' => array('c-ate-devicetype-form-isdevicetopic')),
	   '#default_value' => $topic['IsDeviceTopic'],  
	);	
	
	$form['isusertopic'] = array(
	   '#type' => 'checkbox', 
	   '#title' => 'Is a User topic',
	   '#description' => t('Users will be able to subscribe to this topic'),	
	   '#attributes' => array('class' => array('c-ate-devicetype-form-isusertopic')),
	   '#default_value' => $topic['IsUserTopic'],  
	);			
	
	
	$form['use_event_history'] = array(
	   '#type' => 'checkbox', 
	   '#title' => 'Use Event History',
	   '#description' => t('Past events of this topic will be stored in the event history for a limited period of time'),	
	   '#attributes' => array('class' => array('c-ate-devicetype-form-use-event-history')),
	   '#default_value' => $topic['UseEventHistory'],  
	);			
	
	$form['maxage'] = array(
	  '#type' => 'textfield', 
	  '#title' => 'Max Age (Time To Live)',
	  '#description' => t('Specify the maximum Time To Live for events published to this topic expressed in minutes as an integer e.g 360'),	
	  '#maxlength' => 50,
	  '#attributes' => array('class' => array('c-ate-topic-form-name')),
	  '#default_value' => $topic['formattedMaxAge'], 
	);	
		
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
		'#attributes' => array('class' => array('c-ate-topic-form-submit-btn')),
	);	

	$prefixe = '<div class="row c-ate-topic-form c-topic-form-wrapper">'
			 . '	<div class="col-xs-12 col-sm-5 col-lg-4">';
	$suffix  = '	</div>'
			 . '</div>';
		
	$form['#prefix'] = $prefixe;
	$form['#suffix'] = $suffix;		
	
	return $form;
}

function flowadmin_topic_form_validate($form, &$form_state)
{
	$isDT = ($form_state['values']['isdevicetopic'] != 0) ? true : false;
	$isUT = ($form_state['values']['isusertopic'] != 0) ? true : false;
	$useEH = ($form_state['values']['use_event_history'] != 0) ? true : false;
	$maxAge  = $form_state['values']['maxage'];
	$maxAgeLimits = explode('-', $form_state['values']['maxage_limits']);
	
	$validateResponse = _flowadmin_validate_topic_name($form_state['values']['name']);
	if (!$validateResponse['isvalid']) 
	{
		form_set_error('name', '<div class="'. $validateResponse['error']['ateclasses'].'">'.$validateResponse['error']['msg'].'</div>');
	}
	
	if ((!$isDT) && (!$isUT)) 
	{
		$ateClasses = 'c-ate-topic-form-isdevicetopic-error c-ate-topic-form-isusertopic-error ';
		$msg = t('Please indicate if this topic is a User or Device topic, or both.');
		form_set_error('isdevicetopic', '<div class="'. $ateClasses.'">'. $msg .'</div>');
	}
	
	/**
	 * MaxAge is required only if the use of event history is enabled
	 */
	if ($useEH) 
	{
		/**
		if ($maxAgeLimits[0] > 0) 
		{
			//days converted to minutes
			$maxAgeUpperLimit = (($maxAgeLimits[0] * 1440));
		}
		elseif ($maxAgeLimits[1] > 0)
		{
			//hours
			$maxAgeUpperLimit = $maxAgeLimits[1];
		}
		**/
		// days, hours and minutes 
		$maxAgeUpperLimit = ( ($maxAgeLimits[0] * 1440) + ($maxAgeLimits[1] * 60));
	
		//drupal_set_message('<pre>[flowadmin_topic_form_validate::] MaxAge:: '. print_r(_flowadmin_convert_minutes_to_maxage($maxAge), true).'</pre>');
		//drupal_set_message('<pre>[flowadmin_topic_form_validate::] maxAgeUpperLimit:: '. print_r($maxAgeUpperLimit, true).'</pre>');
			
		//drupal_set_message('maxAge: ' . $maxAge . ', Numeric: ' .is_numeric($maxAge) . ', MaxAgeUpperLimit: ' . $maxAgeUpperLimit);
		if ( !(isset($maxAge) && is_numeric($maxAge) && ($maxAge > 0) && ($maxAge <= $maxAgeUpperLimit)) ) 
		{
			$ateClasses = 'c-ate-topic-form-maxage-error';
			$msg = t('The max age for your account should be between 1 and '. $maxAgeUpperLimit . ', minutes');
			form_set_error('maxage', '<div class="'. $ateClasses.'">'. $msg .'</div>');
		}
	}
	
	
}

function flowadmin_topic_form_submit($form, &$form_state)
{
	global $user;
	
	$name = $form_state['values']['name'];
	$isDT = ($form_state['values']['isdevicetopic'] != 0) ? true : false;
	$isUT = ($form_state['values']['isusertopic'] != 0) ? true : false;
	$useEH = ($form_state['values']['use_event_history'] != 0) ? true : false;
	$maxAge = $form_state['values']['maxage'];
	$formattedMaxAge = '0:00:00';
	$oldTopicName = $form_state['values']['old_topic_name'];
	
	try {
		
		$oauthInfo = flowautho_get_oauth_credentials($user->mail);
		$flowMessagingServices = new FDWFlowMessagingServicesImpl($oauthInfo, $user);
		if ($useEH) 
		{
			//$formattedMaxAge = ((strlen($maxAge) > 0) && (strlen($maxAge) == 1)) ? '0'.$maxAge.':00:00' : $maxAge.':00:00';
			$formattedMaxAge = _flowadmin_convert_minutes_to_maxage($maxAge);
		}
		
		
		if (isset($oldTopicName)) 
		{
			if ($flowMessagingServices->updateTopic($oldTopicName, $name, $isDT, $isUT, $useEH, $formattedMaxAge)) 
			{
				$msg = t('Your new FlowMessaging topic was successfully updated.');
				flowautho_set_message('c-ate-topic-form-updatetopic-success', $msg, 'status', true);
				drupal_goto(FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_TOPICS.'/1');				
			}
			else
			{
				$msg = t('Sorry an error occured while trying to update your FlowMessaging topic.');
				flowautho_set_message('c-ate-topic-form-updatetopic-error', $msg, 'error', false);		
			}			
		}
		else
		{
			if ($flowMessagingServices->createTopic($name, $isDT, $isUT, $useEH, $formattedMaxAge)) 
			{
				$msg = t('Your new FlowMessaging topic was successfully created.');
				flowautho_set_message('c-ate-topic-form-createtopic-success', $msg, 'status', true);
				drupal_goto(FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_TOPICS.'/1');				
			}
			else
			{
				$msg = t('Sorry an error occured while trying to create your FlowMessaging topic.');
				flowautho_set_message('c-ate-topic-form-createtopic-error', $msg, 'error', false);		
			}
		}
		
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWFlowMessagingServicesImpl error:: '. print_r($e->getMessage(),true));
	}	
	
}

function flowadmin_generate_topic_limits_page()
{
	global $user;
	$htmlOutput = null;
	
	flowadmin_access();
		
	$content = '<p>'. t('You have exhausted your FlowMessaging Topics allowance. Please upgrade your plan in order to be able to create more Topics').'</p>';	
	$headerLeft = '';
	$headerRight = '';
	$pageTitle = t('Upgrade Your Subscription') ;
	$htmlOutput =  theme('flowautho_dashboard_content', array('headerLeft'=>'', 'headerCenter' => $pageTitle,  'headerRight' => '', 'mainContent' => $content));
		
	return $htmlOutput;		
}

function flowadmin_delete_topic()
{
	global $user;
	$topicName = func_get_arg(0);
	
	flowadmin_access();	
	
	if (isset($topicName)) 
	{
		try {
			
			$oauthInfo = flowautho_get_oauth_credentials($user->mail);
			$flowMessagingServices = new FDWFlowMessagingServicesImpl($oauthInfo, $user);
			
			if ($flowMessagingServices->deleteTopicByName($topicName)) 
			{
				$msg = t('Your new FlowMessaging topic was successfully deleted.');
				flowautho_set_message('c-ate-topic-form-deletetopic-success', $msg, 'status', true);
				drupal_goto(FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_TOPICS.'/1');			
			}
			else
			{
				$msg = t('Sorry an error occured while trying to delete your FlowMessaging topic.');
				flowautho_set_message('c-ate-topic-form-deletetopic-error', $msg, 'error', false);	
			}
			
		} catch (FDWUnknownUserException $e) {
			watchdog('error', 'FDWFlowMessagingServicesImpl error:: '. print_r($e->getMessage(),true));
		}				
	}
	else
	{
		$msg = t('Sorry we could not find the FlowMessaging topic you are trying to delete.');
		flowautho_set_message('c-ate-topic-form-deletetopic--notopic-error', $msg, 'error', false);			
	}
}

function _flowadmin_validate_topic_name($topicName = null)
{
	$responseContainer = array('isvalid' => false , 'error' => array('msg' => t('Please provide a valid topic name'), 'ateclasses' => 'c-ate-topic-form-name-error'));
	if (isset($topicName)) 
	{
		if (preg_match('/^[a-z0-9]+[a-z0-9-_]+$/i', $topicName)) 
		{
			if (strlen($topicName) > 50) 
			{
				$responseContainer['error']['msg'] = t('The name can have a maximum of 50 characters');
			}
			else
			{
				$responseContainer['isvalid'] = true;
			}
		}
		else
		{
			$responseContainer['error']['msg'] = t('The name should contain only a-z, A-Z, 0123456789, "_" and "-".');
		}
	}
	
	return $responseContainer;
}

function _flowadmin_convert_maxage_string_to_minutes($maxAge = null)
{
	$maxAgeInMinutes = 0;
	if (isset($maxAge)) 
	{
		/**
		 * The expected format is [d.]HH:MM:SS => [days.]HOURS:MINUTES:SECONDS
		 * 
		 * @var unknown_type
		 */
		$maxAgeParts = explode(':', $maxAge);
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
		
		$maxAgeInMinutes = ( ($days * 1440) + ($hours * 60) + $maxAgeParts[1]);
	}
	
	return $maxAgeInMinutes;
}

function _flowadmin_convert_minutes_to_maxage($maxAgeInMinutes = null)
{
	$maxAge = null;
	if (isset($maxAgeInMinutes) && is_numeric($maxAgeInMinutes) && ($maxAgeInMinutes > 0)) 
	{
		$hoursInDay = 24;
		$minutesInHour = 60;
		$secondsInMinute = 60;
		$days = 0;
		$hours = 0;
		$minutes = 0;
		$seconds = 0;
		
		$maxAgeInMinutes = intval($maxAgeInMinutes);
		if ($maxAgeInMinutes < $minutesInHour) 
		{
			$maxAge = ($maxAgeInMinutes > 9) ? '00:'.$maxAgeInMinutes.':00' : '00:0'.$maxAgeInMinutes.':00' ;
		}
		elseif ($maxAgeInMinutes == $minutesInHour)
		{
			$maxAge = '01:00:00';
		}
		elseif ($maxAgeInMinutes > $minutesInHour)
		{
			$tempHours = intval($maxAgeInMinutes/$minutesInHour);
			$tempMinutes = ($maxAgeInMinutes%$minutesInHour); // must be less than 60	
					
			/**
			 * Days
			 */
			if ($tempHours == $hoursInDay) 
			{
				$days = 1;
				$hours = 0;
			}
			elseif ($tempHours < $hoursInDay)
			{
				$days = 0;
				$hours = $tempHours; 
			}
			elseif ($tempHours > $hoursInDay)
			{
				$days = intval($tempHours/$hoursInDay);
				$hours = ($tempHours%$hoursInDay); // must be less than 24
			}

			$displayHours = (strlen($hours) == 2) ? $hours : '0'.$hours;
			$displayMinutes = (strlen($tempMinutes) == 2) ? $tempMinutes : '0'.$tempMinutes;
			$maxAge = ($days > 0) ? $days.'.'.$displayHours.':'.$displayMinutes.':00' : $displayHours.':'.$displayMinutes.':00';
		}
	}
	
	return $maxAge;
}