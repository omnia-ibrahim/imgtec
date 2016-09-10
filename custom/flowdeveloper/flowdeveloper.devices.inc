<?php
/**
 * @file
 * This file contains the function definitions for devices
 */

define('FDW_DEVICES', 'devices');
define('FDW_DEVICES_REGISTER', 'register');
define('FDW_DEVICE', 'device');
define('FDW_MESSAGE_VIEWER', 'msgviewer');
define('FDW_MESSAGE_VIEWER_V2', 'msgviewer-v2');
define('FDW_EDIT', 'edit');
define('FDW_RESOURCES', 'resources');
define('FDW_REG_GUIDE', 'reg-guide');
define('FDW_DELETE', 'delete');


function _flowdeveloper_menu_devices()
{
	$items = array();

	$items[FDW_DASHBOARD.'/'.FDW_DEVICES] = array(
		'title' => t('Devices'),
		'description' => t('Devices list and management'),
		'access callback' => TRUE,
		'page callback' => 'flowdeveloper_generate_devices_page',
		'type' => MENU_NORMAL_ITEM,
		'menu_name' => 'dashboard-menu',
		'weight' => 50,
	);

	$items[FDW_DASHBOARD.'/'.FDW_DEVICE.'/%'] = array(
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowdeveloper_device_detail_page',
		'page arguments' => array(2),
		'type' => MENU_CALLBACK,
		'weight' => 50,
	);

	$items[FDW_DASHBOARD.'/'.FDW_MESSAGE_VIEWER] = array(
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowdeveloper_message_viewer_tool_v2',
		'type' => MENU_CALLBACK,
		'weight' => 50,
	);

	$items[FDW_DASHBOARD.'/'.FDW_MESSAGE_VIEWER_V2] = array(
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowdeveloper_message_viewer_tool',
		'type' => MENU_CALLBACK,
		'weight' => 50,
	);

	/**
	 * Endpoint for retrieving device info
	 **/
	$items[FDW_AJAX.'/'.FDW_DEVICE.'/'.FLOWDEVEL_RETRIEVE_DEVICE_INFO.'/%'] = array(
		'title' => t('Device info retrieval AJAX endpoint'),
		'description' => t('Placeholder page to forward device info to js ajax function'),
		'page callback' => 'flowdeveloper_get_device_info',
		'page arguments' => array(3),
		'access callback' => true,
		'type' => MENU_CALLBACK,
	);

	/**
	 * Endpoint for retrieving device info
	 **/
	$items[FDW_AJAX.'/'.FDW_DEVICE.'/'.FLOWDEVEL_RETRIEVE_DEVICE_STATUS.'/%'] = array(
		'title' => t('Device info retrieval AJAX endpoint'),
		'description' => t('Placeholder page to forward device info to js ajax function'),
		'page callback' => 'flowdeveloper_get_device_status_by_id',
		'page arguments' => array(3),
		'access callback' => true,
		'type' => MENU_CALLBACK,
	);

	/**
	 * Endpoint for updating device info
	 **/
	//$items[FDW_AJAX.'/'.FDW_DEVICE.'/'.FLOWDEVEL_UPDATE_DEVICE_INFO.'/%'.'/%'.'/%'] = array(
	$items[FDW_AJAX.'/'.FDW_DEVICE.'/'.FLOWDEVEL_UPDATE_DEVICE_INFO.'/%'] = array(	
		'title' => t('Device info update AJAX endpoint'),
		'description' => t('Updating device name and description'),
		'page callback' => 'flowdeveloper_device_details_update',
		'page arguments' => array(3),
		'access callback' => true,
		'type' => MENU_CALLBACK,
	);
	
	$items[FDW_AJAX.'/'.FDW_DEVICE.'/%/'.FDW_RESOURCES.'/%/%'] = array(
		'title' => t('Retrieve a Device Resource Instance detail AJAX endpoint'),
		'description' => t('Retrieve a Device Resource Instance detai'),
		'page callback' => 'flowdeveloper_ajax_get_resource_detail',
		'page arguments' => array(2,4,5),
		'access callback' => true,
		'type' => MENU_CALLBACK,
	);


	$items[FDW_DASHBOARD .'/'. FDW_DEVICES .'/'. FDW_DEVICES_REGISTER] = array(
		'title' => t('Device Registration'),
		'description' => t('Register your device with Creator'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowdeveloper_generate_device_registration_page',
		'page arguments' => array(),
		'type' => MENU_CALLBACK,
	);		

	/**
	 * Endpoint for retrieving device registration guide based on selected device type
	 **/
	$items[FDW_AJAX.'/'.FDW_DEVICES.'/'.FDW_REG_GUIDE.'/%'] = array(
		'title' => t('Device registration guide AJAX endpoint'),
		'description' => t('Retrieve device registration guide based on device type'),
		'page callback' => 'flowdeveloper_ajax_get_device_registration_guide',
		'page arguments' => array(3),
		'access callback' => true,
		'type' => MENU_CALLBACK,
	);
	
	/**
	$items[FDW_DASHBOARD .'/'. FDW_DEVICES .'/templateframe'] = array(
		'title' => t('Test Dashboard Template'),
		'description' => t('Test Dashboard Template'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowdeveloper_generate_dashboard_template_test_page',
		'page arguments' => array(),
		'type' => MENU_CALLBACK,
	);
	**/

	$items[FDW_DASHBOARD.'/'.FDW_DEVICE .'/'. FDW_DELETE.'/%'] = array(
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowdeveloper_device_delete',
		'page arguments' => array(3),
		'type' => MENU_CALLBACK,
		'weight' => 50,
	);	

	return $items;
}

function _flowdeveloper_theme_devices()
{
	$themes = array(
		'flowdeveloper_device_list_form' => array(
			'render element' => 'form',
			'template' => 'flowdeveloper.dashboard.devices',
			'path' => drupal_get_path('module', 'flowdeveloper') . '/themes/templates',
		),

		'flowdeveloper_dashboard_device' => array(
			'template' => 'flowdeveloper.dashboard.device',
			'path' => drupal_get_path('module', 'flowdeveloper') . '/themes/templates',
			'type' => 'theme',
			'variables' => array(
				'device' => NULL,
				'status' => NULL,
				'resources' => NULL,
				'locations' => NULL,
			),
		),

		'flowdeveloper_message_viewer_page' => array(
			'template' => 'flowdeveloper.messageviewer',
			'path' => drupal_get_path('module', 'flowdeveloper') . '/themes/templates',
			'type' => 'theme',
			'variables' => array(),
		),

		'flowdeveloper_message_viewer_v2_page' => array(
			'template' => 'flowdeveloper.messageviewerv2',
			'path' => drupal_get_path('module', 'flowdeveloper') . '/themes/templates',
			'type' => 'theme',
			'variables' => array(
				'data' => NULL,
			),
		),
		
		'flowdeveloper_device_resources'  => array(
			'variables' => array('resourceObjects' => NULL, 'deviceID' => NULL),
			//'function' => 'theme_flowdeveloper_device_resources',
			'template' => 'flowdeveloper.dashboard.devices.resources',
			//'path' => drupal_get_path('module', 'flowdeveloper') . "/themes",
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes/templates",
			//'file' => 'flowdeveloper.theme.dashboard.inc',		
		),	

		
		'flowdeveloper_device_resource_instance'  => array(
			'variables' => array('resourceInstance' => NULL, 'objectID' => NULL, 'instanceID' => NULL),
			'function' => 'theme_flowdeveloper_resource_instance',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes",
			'file' => 'flowdeveloper.theme.dashboard.inc',		
		),	

		'flowdeveloper_device_resource_instance_list_item'  => array(
			'variables' => array('extraClasses' => NULL, 'instanceID' => NULL, 'objectID' => NULL, 'deviceID' => NULL, 'instanceCount' => NULL),
			'template' => 'flowdeveloper.dashboard.devices.resource_list_item',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes/templates",
		),

		'flowdeveloper_device_registration'  => array(
			'variables' => array('deviceTypesForm' => NULL, 'FCAPCode' => NULL),
			'template' => 'flowdeveloper.dashboard.devices.registration',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes/templates",
		),
		
		'flowdeveloper_device_powersource'  => array(
			'variables' => array('powerSource' => NULL),
			'template' => 'flowdeveloper.dashboard.devices.powersource',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes/templates",
		),	

		'flowdeveloper_device_storage'  => array(
			'variables' => array('storageItem' => NULL),
			'template' => 'flowdeveloper.dashboard.devices.storage',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes/templates",
		),			


		'flowdeveloper_device_geolocation'  => array(
			'variables' => array('locationData' => NULL),
			'template' => 'flowdeveloper.dashboard.devices.geolocation',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes/templates",
		),	
	);

	return $themes;
}

/**
 * Generate related devices page depending on the argument supplied
 */
function flowdeveloper_generate_devices_page()
{
	global $user;

	$deviceManServices = null;

	if(user_is_anonymous()) {
		drupal_goto('user/login');
	}

	$oauthInfo = flowautho_get_oauth_credentials($user->mail);

	$devices =  array();
	try {
		//Create a device management services object and retrieve the code
		$deviceManServices = new FDWDeviceManagementServicesImpl($oauthInfo, $user);
		$devices = $deviceManServices->getDevices(1, 20);
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceManagementServicesImpl error:: '. print_r($e->getMessage(),true));
	}

	$deviceListForm = drupal_get_form('flowdeveloper_device_list_form',$devices);
	$headerRight = '<a class="c-ate-devices-register-link" href="'.url(FDW_DASHBOARD.'/'.FDW_DEVICES.'/'.FDW_DEVICES_REGISTER).'">'
				 . '	<button type="button" class="btn btn-default c-devices-register-btn c-ate-devices-register-btn hidden-xs"><span class="cp-icon"></span>'.t('Register').'</button>'
				 . '	<button type="button" class="btn btn-default c-devices-register-btn c-ate-devices-register-btn hidden-sm hidden-md hidden-lg"><span class="cp-icon q-mobile"></span></button>'	
				 . '</a>';  
    $mainContent = drupal_render($deviceListForm);
    			 

    return theme('flowautho_dashboard_content', array('headerLeft' => '', 
				        	  'headerCenter' => t('Devices'),  
						  'headerRight' => $headerRight, 
						  'mainContent' => $mainContent));	

}

/**
 *
 */
function flowdeveloper_message_viewer_tool()
{

	global $user;

	//Only logged in users, sorry.
	if(user_is_anonymous()) {
		drupal_goto('user/login');
	}

	//Let's include the library first.
	drupal_add_js(libraries_get_path('sip') . '/sip-0.7.0.js'); //, array('group' => JS_THEME, 'every_page' => TRUE)

	//TODO: check if the library is loaded if not throw an exception.
	//TODO: use try and catch in below and throw an exception if settings can't be retrieved.

	//Get user sip credentials
	$authCredentials = flowautho_get_oauth_credentials($user->mail);
	$fdwUserServices = new FDWUserServicesImpl($authCredentials, $user);
	$userSipCredentials = $fdwUserServices->getFlowMessagingSettings();

	//Mapping
	$userSipSettings = Array(
		"URI" => $userSipCredentials['Address'],
		"UserName" => $userSipCredentials['UserName'],
		"PasswordHash" => $userSipCredentials['PasswordHash'],
		"DisplayName" => $userSipCredentials['UserName'],
		"GUID" => $user->data['lounge2_guid'],
		"SIPDomain" => $userSipCredentials['SIPDomain']
	);


	//Get user devices
	$fdwDevicemanServices = new FDWDeviceManagementServicesImpl($authCredentials, $user);
	$userDevices = $fdwDevicemanServices->getDevices();

	//Get device IDs in an array
	$device_ids = Array();
	foreach($userDevices as $device){
		$device_ids[] = $device['DeviceID'];
	}

	//Use the array to grab settings for each.
	$flow_messages_settings_for_user_devices = Array();
	foreach($device_ids as $device_id){
		$flow_messages_settings_for_user_devices[] = $fdwDevicemanServices->getDeviceFlowMessagingSettingsByID($device_id);
	}

	//Then trim settings to only have what we need.
	$stripped_device_settings = Array();
	$i = -1; //little hack. Sorry.
	if($flow_messages_settings_for_user_devices){
		foreach($flow_messages_settings_for_user_devices as $device_settings){
			$i++;
			$stripped_device_settings[] = Array(
				"URI" => $device_settings['Identity'],
				"UserName" => $device_settings['ServiceEndPoints'][0]['Username'],
				"PasswordHash" => $device_settings['ServiceEndPoints'][0]['PasswordHash'],
				"DisplayName" => $device_settings['ServiceEndPoints'][0]['Username'],
				"GUID" => $device_ids[$i]
			);
		}
	}

	//We need three fields to register to SIP server - Kamilio.
	//Pass them onto JS
	drupal_add_js(array('flowSip' => array(
		'user_devices_sip_settings' => json_encode($stripped_device_settings),
		'user_sip_settings' => json_encode($userSipSettings),
		'FDW_MESSAGE_VIEWER_V2' => FDW_MESSAGE_VIEWER_V2,
		'FDW_MESSAGE_VIEWER' => FDW_MESSAGE_VIEWER
	)), 'setting');

	return theme('flowdeveloper_message_viewer_page');
}

function flowdeveloper_message_viewer_tool_v2()
{

	global $user;

	//Only logged in users, sorry.
	if(user_is_anonymous()) {
		drupal_goto('user/login');
	}

	//Let's include the library first.
	drupal_add_js(libraries_get_path('sip') . '/sip-0.7.0.js'); //, array('group' => JS_THEME, 'every_page' => TRUE)

	try {
		$oauthInfo = flowautho_get_oauth_credentials($user->mail);
		$fdwUserServices = new FDWUserServicesImpl($oauthInfo, $user);
		$fdwDeviceServices = new FDWDeviceManagementServicesImpl($oauthInfo, $user);
		$userSipCredentials = $fdwUserServices->getFlowMessagingSettings();
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceManagementServicesImpl error:: '. print_r($e->getMessage(),true));
	}


	//Mapping
	$userSipSettings = Array(
		"URI" => $userSipCredentials['Address'],
		"UserName" => $userSipCredentials['UserName'],
		"PasswordHash" => $userSipCredentials['PasswordHash'],
		"DisplayName" => $userSipCredentials['UserName'],
		"SIPDomain" => $userSipCredentials['SIPDomain']
	);

	try {

		//Get user topics
		$user_fm_topics = $fdwUserServices->getFlowMessagingTopics();


		//Get user devices
		$userDevices = $fdwDeviceServices->getDevices();

		//Get device IDs in an array
		$device_ids = Array();
		foreach($userDevices as $device){
			$device_ids[] = $device['DeviceID'];
		}

		$device_fm_topics = Array();
		foreach($device_ids as $device_id){
			$device_details_array = $fdwDeviceServices->getDevice($device_id);
			$device_details = Array("DeviceID"=>$device_id, "DeviceName"=> $device_details_array['DeviceName']);
			//TODO: check canuseflowmessaging
			$device_topics = $fdwDeviceServices->getFlowMessagingTopics($device_id);
			$device_fm_topics[] = $device_topics + $device_details;
		}

	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceManagementServicesImpl error:: '. print_r($e->getMessage(),true));
	}

	$data = Array(
		"user_fm_topics" => $user_fm_topics,
		"device_fm_topics" => $device_fm_topics
	);

	drupal_add_js(array('flowSip' => array(
		'user_sip_settings' => json_encode($userSipSettings),
		'user_guid' => $user->name,
		'FDW_MESSAGE_VIEWER_V2' => FDW_MESSAGE_VIEWER_V2,
		'FDW_MESSAGE_VIEWER' => FDW_MESSAGE_VIEWER
	)), 'setting');

	return theme('flowdeveloper_message_viewer_v2_page', array('data' => $data));
}

function flowdeveloper_get_device_info($device_id){
	global $user;

	$deviceManServices = null;

	if(user_is_anonymous()) {
		drupal_goto('user/login');
	}

	$oauthInfo = flowautho_get_oauth_credentials($user->mail);

	try {
		//Create a device management services object and retrieve the code
		$deviceManServices = new FDWDeviceManagementServicesImpl($oauthInfo, $user);
		$device = $deviceManServices->getDevice($device_id);
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceManagementServicesImpl error:: '. print_r($e->getMessage(),true));
	}

	$device_json = json_encode($device);

	//Result needs to be echoed rather than returned as per AJAX usage.
	echo $device_json;
}

function flowdeveloper_get_device_status_by_id($deviceID){
	global $user;

	$deviceManServices = null;

	if(user_is_anonymous()) {
		drupal_goto('user/login');
	}

	$oauthInfo = flowautho_get_oauth_credentials($user->mail);

	$device_status = null;
	try {
		//Create a device management services object and retrieve the code
		$deviceManServices = new FDWDeviceManagementServicesImpl($oauthInfo, $user);
		$device_status = $deviceManServices->getStatusPartial($deviceID);
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceManagementServicesImpl error:: '. print_r($e->getMessage(),true));
	}
	
	$date = new DateTime($device_status['LastSeenTime']);
	$device_status['LastSeenTime'] = t('Last online').' '.$date->format('d M');

	echo json_encode($device_status);
}

function flowdeveloper_device_detail_page($device_id)
{
	global $user;

	$deviceManServices = null;

	if(user_is_anonymous()) {
		drupal_goto('user/login');
	}

	$oauthInfo = flowautho_get_oauth_credentials($user->mail);

	try {
		//Create a device management services object and retrieve the code
		$deviceManServices = new FDWDeviceManagementServicesImpl($oauthInfo, $user);
		$device = $deviceManServices->getDevice($device_id);

		//Set title of the page here
		drupal_set_title($device['DeviceName']);

		
		$deviceStatus = $deviceManServices->getStatus($device_id);
		$storage = $deviceManServices->getStorageInfo($device_id);
		$locations = $deviceManServices->getLocations($device_id);
		
		//drupal_set_message('<pre>DeviceStatus'. print_r($deviceStatus, TRUE).'</pre>');
		//################################## test data #####################################
		/**
		$deviceStatus['Storage'][] = array(
		
			'Name' => 'External',
			'StorageType' => 'SD Card',
			'FreeStorage' => array('Value' => '600','Unit' => 'kb'),
			'TotalStorage' => array('Value' => '5','Unit' => 'MB'),
		);
		**/
		//################################## test data #####################################
		
		$normalizedStorage = flowdeveloper_device_normalize_storage_info($deviceStatus['Storage']);
		$deviceStatus['NormalizedStorageInfo'] = $normalizedStorage;
		
		//################################## test data #####################################
		/**
		$powerSources[] =  array(
		
			'PowerSourceType' => 'InternalBattery',
			'Status' => 'Charging',
			'Level' => '85',
			'Voltage' => array('Value' => '1500', 'Unit' => 'mV', 'MeasurementType' => null),
			'Current' => array('Value' => '50', 'Unit' => 'mA', 'MeasurementType' => null),
			'Power' => array('Value' => '18', 'Unit' => 'W', 'MeasurementType' => 'RMS')		
		);
		**/
		/**
		$powerSources[] =  array(
		
			'PowerSourceType' => 'InternalBattery',
			'Status' => 'Unknown',
			//'Level' => '85',
			//'Voltage' => array('Value' => '1500', 'Unit' => 'mV', 'MeasurementType' => null),
			//'Current' => array('Value' => '50', 'Unit' => 'mA', 'MeasurementType' => null),
			//'Power' => array('Value' => '18', 'Unit' => 'W', 'MeasurementType' => 'RMS')		
		);
				
		$powerSources[] =  array(
		
			'PowerSourceType' => 'AC',
			'Status' => 'Disconnected',
			'Level' => null,
			'Voltage' => array('Value' => '25', 'Unit' => 'V', 'MeasurementType' => 'RMS'),
			'Current' => array('Value' => '1100', 'Unit' => 'mA', 'MeasurementType' => 'RMS'),
			'Power' => array('Value' => '16', 'Unit' => 'W', 'MeasurementType' => 'RMS')		
		);
		
		$powerSources[] =  array(
		
			'PowerSourceType' => 'DC',
			'Status' => 'Disconnected',
			'Level' => null,
			'Voltage' => array('Value' => '25', 'Unit' => 'V', 'MeasurementType' => 'RMS'),
			'Current' => array('Value' => '1100', 'Unit' => 'mA', 'MeasurementType' => 'RMS'),
			'Power' => array('Value' => '16', 'Unit' => 'W', 'MeasurementType' => 'RMS')		
		);	

		$powerSources[] =  array(
		
			'PowerSourceType' => 'USB',
			'Status' => 'Connected',
			'Level' => null,
			'Voltage' => array('Value' => '25', 'Unit' => 'V', 'MeasurementType' => 'RMS'),
			'Current' => array('Value' => '1100', 'Unit' => 'mA', 'MeasurementType' => 'RMS'),
			'Power' => array('Value' => '16', 'Unit' => 'W', 'MeasurementType' => 'RMS')		
		);


		$powerSources[] =  array(
		
			'PowerSourceType' => 'ExternalBattery',
			'Status' => 'Connected',
			'Level' => null,
			'Voltage' => array('Value' => '25', 'Unit' => 'V', 'MeasurementType' => 'RMS'),
			'Current' => array('Value' => '1100', 'Unit' => 'mA', 'MeasurementType' => 'RMS'),
			'Power' => array('Value' => '16', 'Unit' => 'W', 'MeasurementType' => 'RMS')		
		);		

		$powerSources[] =  array(
		
			'PowerSourceType' => 'Solar',
			'Status' => 'Disconnected',
			'Level' => null,
			'Voltage' => array('Value' => '25', 'Unit' => 'V', 'MeasurementType' => 'RMS'),
			'Current' => array('Value' => '1100', 'Unit' => 'mA', 'MeasurementType' => 'RMS'),
			'Power' => array('Value' => '16', 'Unit' => 'W', 'MeasurementType' => 'RMS')		
		);			
		**/
		
		//$deviceStatus['PowerSources'] = $powerSources;
		//$deviceStatus['Online'] = true;
		
		
		//####################################################################################
		
		if (isset($deviceStatus['LastSeenTime'])) 
		{
			$date = new DateTime($deviceStatus['LastSeenTime']);
			$deviceStatus['LastSeenTime'] = $date->format('d M');
		}
		else
		{
			$deviceStatus['LastSeenTime'] = t('Unknown');
		}
		
		$resourceObjects = $deviceManServices->findDeviceResourceClassesByDeviceID($device_id);
		/*$additionalTestInstances[] =  array("InstanceID" => 0, 'Links' => 'https://ws-uat.flowworld.com/devices/4ed5ed06-7d54-4dcd-b134-5656667cc2cf/resources/9K5weL29n0Knbj3cY--nxw/instances/0');
		$additionalTestInstances[] =  array("InstanceID" => 1, 'Links' => 'https://ws-uat.flowworld.com/devices/4ed5ed06-7d54-4dcd-b134-5656667cc2cf/resources/9K5weL29n0Knbj3cY--nxw/instances/0');	
		$additionalTestInstances[] =  array("InstanceID" => 2, 'Links' => 'https://ws-uat.flowworld.com/devices/4ed5ed06-7d54-4dcd-b134-5656667cc2cf/resources/9K5weL29n0Knbj3cY--nxw/instances/0');
		$resourceObjects[] = array(
			'ObjectID' => '50000',
			'Name' => 'JKelTestObject',
			'MIMEType' => 'application/vnd.oma.lwm2m.ext.flowobject',
			'Instances' => $additionalTestInstances
		);*/
		$themedResourceObjects = theme('flowdeveloper_device_resources', array('resourceObjects' => $resourceObjects, 'deviceID' => $device_id));
		
		if (isset($deviceStatus['PowerSources'])) 
		{
			for ($i = 0; $i < count($deviceStatus['PowerSources']); $i++) 
			{
				switch ($deviceStatus['PowerSources'][$i]['Status']) {
					case "ChargeComplete":
						$status = t('Charge Complete');
						break;
					case "Charging":
						$status = t('Charging');
						break;
					case "Damaged":
						$status = t('Damaged');
						break;
					case "Low Battery":
						$status = t('Low Battery');
						break;
					case "Not Installed":
						$status = t('Not Installed');
						break;					
					case "Unknown":
						$status = t('Unknown');
						break;
					default:
						$status = $deviceStatus['PowerSources'][$i]['Status'];
				}
				$deviceStatus['PowerSources'][$i]['Status'] = $status;
			}			
		}

	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceManagementServicesImpl error:: '. print_r($e->getMessage(),true));
	}
	
	$headerLeft = '<a href="'. base_path().'dashboard/devices">'
				. '	<button type="button" class="btn btn-default c-back-btn">'
				. '		<span class="cp-icon"></span>Devices'
				. ' </button>'
				. '	</a>';				
				
	$deleteDevicePath = base_path() .FDW_DASHBOARD.'/'.FDW_DEVICE .'/'. FDW_DELETE.'/'. $device_id;
				
	$headerRight = '<a href="'. $deleteDevicePath.'" class="q-delete-device">'	
				 . '	<button type="button" class="btn btn-default c-ate-delete-device-btn c-alt-delete-device-btn hidden-xs">'
				 . '		<span class="cp-icon"></span>Delete'
				 . '	</button>'
				 . '	<button type="button" class="btn btn-default c-ate-delete-device-btn c-alt-delete-device-btn hidden-sm hidden-md hidden-lg"><span class="cp-icon q-mobile"></span></button>'
				 . '</a>'
				 ;
				 
	$mainContent = theme('flowdeveloper_dashboard_device', array(	'device' => $device, 
																	'status' => $deviceStatus, 
																	'resources' => $themedResourceObjects,
																	'locations' => $locations));
	
	return theme('flowautho_dashboard_content', array('headerLeft' => $headerLeft, 
													  'headerCenter' => $device['DeviceName'],  
													  'headerRight' => $headerRight, 
													  'mainContent' => $mainContent));	

	//return theme('flowdeveloper_dashboard_device', array('device' => $device, 'status' => $deviceStatus, 'resources' => $themedResourceObjects));
}

function flowdeveloper_device_details_update()
{
	global $user;
	
	$deviceIDAux = func_get_arg(0);
	$deviceID = $_POST['_deviceid'];
	$newName = $_POST['_newname'];
	$newDescription = $_POST['_newdesc'];

	try {

		$newDescription = (isset($newDescription) && (strlen($newDescription) > 0)) ? $newDescription : '   ';
		if (isset($deviceID) && isset($newName) && (strlen($newName) > 0)) 
		{
			$oauthInfo = flowautho_get_oauth_credentials($user->mail);
			$deviceManServices = new FDWDeviceManagementServicesImpl($oauthInfo, $user);
			if ($deviceManServices->updateBasicDeviceInfo($deviceID, $newName, $newDescription))
			{
				//drupal_goto(FDW_DASHBOARD .'/'. FDW_DEVICE .'/'. $deviceID);
				echo true;
			}
			else
			{
				echo false;
				//$msg = 'An Error occured while trying to update your device info.';
				//flowautho_set_message('c-ate-device-update-error', $msg, 'error');
			}			
		}
		else
		{
			echo false;
		}

	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceManagementServicesImpl error:: '. print_r($e->getMessage(),true));
	}
}


function flowdeveloper_ajax_get_resource_detail()
{
	global $user;	
	$deviceID = func_get_arg(0);
	$resourceObjectID = func_get_arg(1);
	$instanceID = func_get_arg(2);
	$notFound = '<p>'. t('No instance could be found with the supplied ID. Check if the device is online') .'</p>';
	$ajaxResponse = $notFound;
	
	if (isset($deviceID) && isset($resourceObjectID) && isset($instanceID)) 
	{
		try {
			
			$oauthInfo = flowautho_get_oauth_credentials($user->mail);
			$deviceManServices = new FDWDeviceManagementServicesImpl($oauthInfo, $user);
			$instanceDetails = $deviceManServices->findDeviceResourceInstance($deviceID, $resourceObjectID, $instanceID);
			//_flowautho_debug('[flowdeveloper_ajax_get_resource_detail:: ] Details: '. print_r($instanceDetails, true)	);
			if (is_array($instanceDetails) && (count($instanceDetails['Properties']) > 0 )) 
			{
				$args = array('resourceInstance' => $instanceDetails, 'objectID' => $resourceObjectID, 'instanceID' => $instanceID);
				$ajaxResponse = theme('flowdeveloper_device_resource_instance', $args);	
					
			}
			else
			{
				$ajaxResponse = $notFound;
			}
			
		} catch (FDWUnknownUserException $e) {
			watchdog('error', 'FDWDeviceManagementServicesImpl error:: '. print_r($e->getMessage(),true));
		}
	}
	
	//_flowautho_debug('[flowdeveloper_ajax_get_resource_detail:: ] DeviceID:: '. $deviceID . ', ObjectID:: '. $resourceObjectID . ', InstanceID:: '. $instanceID);
	//_flowautho_debug('[flowdeveloper_ajax_get_resource_detail:: ] Details: '. print_r($ajaxResponse, true)	);

	drupal_add_http_header('Content-Type', 'text/html; charset=utf-8');
	echo $ajaxResponse;
}

function flowdeveloper_device_delete_form($form, &$form_state, $deviceID, $deviceName)
{
	$form = array();

	$form['deviceCount'] = array(
		'#type' => 'hidden',
		'#value' =>1,
	);

	$form['device'] = array(
		'#type' => 'hidden',
		'#value' =>$deviceID,
	);

	$form['deviceName'] = array(
		'#type' => 'hidden',
		'#value' =>$deviceName,
	);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Delete'),
		'#attributes' => array('class' => array('c-delete-device-btn c-ate-delete-device-btn')),
	);

	$form['#submit'][] = 'flowdeveloper_device_delete_submit';

	return $form;
}

function flowdeveloper_device_list_form($form, &$form_state, $devices)
{
	$i = 0;
	$form = array();

	$deviceCount = count($devices);

	$form['deviceCount'] = array(
		'#type' => 'hidden',
		'#value' => $deviceCount,
		'#attributes' => array('class' => array('c-device-count')),
	);
	
	$form['selected_devices'] = array(
		'#type' => 'hidden',
		'#default_value' => '',
		'#attributes' => array('class' => array('c-device-selected-devices')),
	);	

	foreach ($devices as $device) {
		
		$name = 'selected-device-'.$i;
		//$form['devices'][$i] = array(
		$form['devices'][$name] = array(
			'#type' => 'checkbox',
			'#title' => '',
			'#default_value' => false,
			'#return_value' => $device['DeviceID'],
			'#attributes' => array(
				'class' => array('checkbox-primary c-device-chk'),
				'deviceid' => array($device['DeviceID']),
				'devicename' => array($device['DeviceName']),
				'devicedesc' => array($device['Description']),
				'ismanagable' => array($device['IsManagable']),
				'autocomplete' => 'off'
			),
			'#label_class' => 'c-ate-device-chk-'.($i+1),
		);

		$i++;
	}

	/*$form['submit'] = array(
		'#type' => 'image_button',
		'#src' => path_to_theme().'/images/icons/ic-delete.png',
		'#value' => t('Test'),
		'#attributes' => array('class' => array('c-delete-device-btn')),
	);*/
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Delete'),
		'#attributes' => array('class' => array('c-sudo-delete-device-btn')),
	);

	$form['#submit'][] = 'flowdeveloper_device_delete_submit';
	
	

	return $form;
}

function flowdeveloper_device_delete_submit($form, &$form_state)
{
	global $user;

	$deviceCount = $form_state['values']['deviceCount'];
	
	$selectedDevices = explode('|',$form_state['values']['selected_devices']);
	$dsCount = count($selectedDevices);
	unset($selectedDevices[($dsCount-1)]);
	
	if($deviceCount) {
		$successCount = 0;
		$errorCount = 0;
		$oauthInfo = flowautho_get_oauth_credentials($user->mail);
		$deviceManServices = new FDWDeviceManagementServicesImpl($oauthInfo, $user);
		$device_id = array();
		$noDeviceSelected = false; 

		/**
		if(isset($form_state['values']['device'])) {
			$device_id[] = $form_state['values']['device'];
		} else {
			for($i=0; $i<$deviceCount; $i++) {
				$name = 'selected-device-'.$i;
				/**
				if( isset($form_state['values'][$i]) && (strlen($form_state['values'][$i]) > 5)) {
					$device_id[] = $form_state['values'][$i];
				}
				**/
		/**
				if( isset($form_state['values'][$name]) && (strlen($form_state['values'][$name]) > 5)) {
					$device_id[] = $form_state['values'][$name];
				}
			}
		}
		**/
		
		//drupal_set_message('<pre>DeviceList:: '. print_r($form_state['values'], true).'</pre>');
		//drupal_set_message('<pre>DevicesToDelete:: '. print_r($device_id, true).'</pre>');
		
		if (count($selectedDevices) > 0) 
		{
			foreach($selectedDevices as $device) {
				if ($deviceManServices->deleteDeviceByID($device)) {
					$successCount++;
				}
				else {
					$errorCount++;
				}
			}
		}
		else
		{
			$noDeviceSelected = true;
		}

		if($errorCount) {
			$msg = 'Failed to delete '.$errorCount.' devices.';
			flowautho_set_message('c-ate-device-update-error', $msg, 'error');
		} else if($successCount) {
			$msg = 'One or more selected devices have been deleted.';
			flowautho_set_message('c-ate-device-update-error', $msg, 'status');
			drupal_goto(FDW_DASHBOARD . '/' . FDW_DEVICES);
		} 
		elseif ($noDeviceSelected)
		{
			$msg = 'No devices were deleted because none was selected.';
			flowautho_set_message('c-ate-device-update-error', $msg, 'error');
		}
	}
}

/**
 *
 */
function flowdeveloper_generate_device_registration_page()
{
	global $user;
	$oauthInfo = flowautho_get_oauth_credentials($user->mail);
	
	try {
		
			$deviceManServices = new FDWDeviceManagementServicesImpl($oauthInfo, $user);
			$responseContainer = $deviceManServices->getFCAPCode();
			$fcapCode = $responseContainer['fcapcode'];
			
			//drupal_set_message('<pre>FCAPCode:: '.print_r($responseContainer, true).'</pre>');
			//drupal_set_message('<pre>Formatted ExpiryDate:: '.print_r(flowdeveloper_utcTimeToDateTime($responseContainer['expdate']), true).'</pre>');
			
			//$fcapCode = null;
			
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceManagementServicesImpl error:: '. print_r($e->getMessage(),true));
	}	
	
	drupal_set_title(t('Register Device'));
//	return theme('flowdeveloper_device_registration', array('deviceTypesForm' => drupal_get_form('flowdeveloper_device_registration_form'), 'FCAPCode' => $fcapCode) );
    $mainContent = theme('flowdeveloper_device_registration', array('deviceTypesForm' => drupal_get_form('flowdeveloper_device_registration_form'), 'FCAPCode' => $responseContainer) );
    return theme('flowautho_dashboard_content', array('headerLeft' => '', 
		       				  'headerCenter' => t('Register Device'),  
						  'headerRight' => '', 
		        			  'mainContent' => $mainContent));	

}

/**
 *
 */
function flowdeveloper_device_registration_form($form, &$form_state)
{
	global $user;
	
	$oauthInfo = flowautho_get_oauth_credentials($user->mail);
	$form = array();
	
	try {
		
			$deviceManServices = new FDWDeviceManagementServicesImpl($oauthInfo, $user);
			$deviceTypes = $deviceManServices->getDeviceTypes(1, 200);
			
			$defaultDeviceType = t('select device type');
			$deviceTypesOptions[0] =  t('select device type');

			foreach ($deviceTypes as $dt) 
			{
				$id = $dt['DeviceTypeID'];
				$name = $dt['Name'];
				//$deviceTypesOptions[$id] = $name;
				$deviceTypesOptions[$name] = $name;
			}
			
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceManagementServicesImpl error:: '. print_r($e->getMessage(),true));
	}
	
	$form['device_type'] = array(
		'#type' => 'select',
		'#title' => 'Device Types',
		'#description' => 'Select your device type to see the registration instructions.',
		'#options' => $deviceTypesOptions,
		'#default_value' => $defaultDeviceType, 
		'#required' => TRUE,
		'#weight' => 1,
		'#attributes' => array('class' => array('c-ate-device-reg-devicetype-list')),
	);
	
	unset($form['device_type']['#title']);
	unset($form['device_type']['#description']);	
	
	return $form;	
}



function flowdeveloper_ajax_get_device_registration_guide()
{
	global $user, $base_path;	
	$deviceType = strtolower(func_get_arg(0));
	$default = 'Default device registration quide is not available at this time';
	$ajaxResponse = $default;	
	
	if (isset($deviceType)) 
	{
		$vocabMachineName = FDW_DEVICETYPE_VOCAB_MACHINE_NAME;
		if (isset($vocabMachineName)) 
		{
			$vocab = taxonomy_vocabulary_machine_name_load($vocabMachineName);
			if (isset($vocab->vid)) 
			{
				$query = new EntityFieldQuery();
				$query->entityCondition('entity_type', 'taxonomy_term');
				$query->propertyCondition('vid', $vocab->vid, '=');
				$terms = $query->execute();
				
				if (count($terms['taxonomy_term'])) 
				{
					$defaultGuide = null;
					$selectedGuide = null;
					foreach ($terms['taxonomy_term'] as $to) 
					{
						$term = taxonomy_term_load($to->tid);
						if ($term !== false) 
						{
							if (strtolower($term->name) == 'default') 
							{
								$defaultGuide = $term->description;
							}
							elseif (strtolower($term->name) == $deviceType)
							{
								$selectedGuide = $term->description;
								break;
							}
						}
					}
					
					if (isset($selectedGuide)) 
					{
						$ajaxResponse = $selectedGuide;
					}
					elseif (isset($defaultGuide))
					{
						$ajaxResponse = $defaultGuide;
					}
				}

			}
		}		
	}
	
	$ajaxResponse .= '<div class="cp-footnote">Once registered your device will appear under <a href="'. $base_path.FDW_DASHBOARD."/".FDW_DEVICES .'" class="c-ate-devices-list-link">Devices</a>.</div>';
	
	drupal_add_http_header('Content-Type', 'text/html; charset=utf-8');
	echo $ajaxResponse;
}

function flowdeveloper_generate_dashboard_template_test_page()
{
	
	return theme('flowdeveloper_dashboard_content', array('headerLeft' => 'Page Navigation', 
														  'headerCenter' => 'Dashboard Content Template', 
														  'headerRight' => 'Page Controls', 
														  'mainContent' => ' <br/><br/><br/><br/><br/><br/>--- Main Content --- '));
}

/**
 * Page callback function to delete a single device 
 */
function flowdeveloper_device_delete()
{
	global $user;
	$deviceID = func_get_arg(0);
	
	try {
			$oauthInfo = flowautho_get_oauth_credentials($user->mail);
			$deviceManServices = new FDWDeviceManagementServicesImpl($oauthInfo, $user);
			if ($deviceManServices->deleteDeviceByID($deviceID)) 
			{
				flowautho_set_message('c-ate-device-delete-success', 'The device was successfully deleted', 'status', true);
				drupal_goto(FDW_DASHBOARD.'/'.FDW_DEVICES);
			}
			else 
			{
				flowautho_set_message('c-ate-device-delete-error', 'Failed to delete the device. Please try again later', 'error', true);
				drupal_goto(FDW_DASHBOARD.'/'.FDW_DEVICE .'/'. $deviceID);
			}
		
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceManagementServicesImpl error:: '. print_r($e->getMessage(),true));
	}
}

function flowdeveloper_device_normalize_storage_info(array $storageInfoContainer=null)
{
	$normalizedSI = null;
	
	if (isset($storageInfoContainer)) 
	{
		$normalizedSI = array();
		foreach ($storageInfoContainer as $storageItem) 
		{
			if ( (count($storageItem['FreeStorage']) > 0) && (count($storageItem['TotalStorage']) > 0) ) 
			{
				$freeUnit = strtolower($storageItem['FreeStorage']['Unit']);
				$totalUnit = strtolower($storageItem['TotalStorage']['Unit']);
				$free = $storageItem['FreeStorage']['Value'];
				$total = $storageItem['TotalStorage']['Value'];
				
				if ($freeUnit !== $totalUnit) 
				{
					if (($freeUnit == FDW_UNIT_BYTES) && ($totalUnit == FDW_UNIT_KILOBYTE)) 
					{
						$total = flowdeveloper_convert_storage_units($storageItem['TotalStorage']['Value'], FDW_UNIT_KILOBYTE, FDW_UNIT_BYTES);
						$storageItem['TotalStorage']['Unit'] = $freeUnit;
					}
					elseif (($freeUnit == FDW_UNIT_KILOBYTE) && ($totalUnit == FDW_UNIT_MEGABYTE))
					{
						$total = flowdeveloper_convert_storage_units($storageItem['TotalStorage']['Value'], FDW_UNIT_MEGABYTE, FDW_UNIT_KILOBYTE);
						$storageItem['TotalStorage']['Unit'] = $freeUnit;
					}
				}
				
				$storageItem['FreeStorage']['Value'] = $free;
				$storageItem['TotalStorage']['Value'] = $total;
				$storageItem['UsedStorage']['Value'] = ($total - $free);
				$storageItem['UsedStorage']['Unit'] = $storageItem['FreeStorage']['Unit']; // An assumption
			}

			$normalizedSI[] = $storageItem;
		}
	}
	
	return $normalizedSI;
}
