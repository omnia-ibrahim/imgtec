<?php

define('FLOWADMIN_DASHBOARD', 'dashboard');
define('FLOWADMIN', 'flowadmin');
define('FLOWADMIN_DEVICETYPES', 'device-types');
define('FLOWADMIN_ADD', 'add');
define('FLOWADMIN_EDIT', 'edit');
define('FLOWADMIN_DELETE', 'delete');

/**
 * Return a list of device types related menu paths
 * Enter description here ...
 */
function _flowadmin_menu_devicetypes()
{
	$items = array();
	
	$items[FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES.'/%'] = array(
		'title' => t('Device Types'),
		'description' => t('Device types list'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowadmin_generate_devicetypes_page',
		'page arguments' => array(3),
		'type' => MENU_NORMAL_ITEM,
		'weight' => 50,
	);	
	
	$items[FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES.'/'.FLOWADMIN_ADD] = array(
		'title' => t('Add Device Type'),
		'description' => t('Add a new Device type to a particular tenant'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowadmin_generate_add_devicetype_page',
		'page arguments' => array(NULL),
		'type' => MENU_NORMAL_ITEM,
		'weight' => 50,
	);	
	
	$items[FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES.'/%/'.FLOWADMIN_EDIT] = array(
		'title' => t('Edit Device Type'),
		'description' => t('Edit and existing Device type specification'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowadmin_generate_add_devicetype_page',
		'page arguments' => array(3),
		'type' => MENU_NORMAL_ITEM,
		'weight' => 50,
	);		
	
	$items[FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES.'/%/'.FLOWADMIN_DELETE] = array(
		'title' => t('Delete Device Type'),
		'description' => t('Delete a Device type'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowadmin_delete_devicetype',
		'page arguments' => array(3),	
		'type' => MENU_NORMAL_ITEM,
		'weight' => 50,
	);		
	
	return $items;
}

function _flowadmin_theme_devicetypes()
{
	$items = array(
	
		'flowadmin_devicetypes_headerright'  => array(
			'variables' => array('url' => NULL),
			'template' => 'flowadmin.devicetypes.headerright',
			'path' => drupal_get_path('module', 'flowadmin') . "/themes",
		),	

		'flowadmin_devicetypes_maincontent'  => array(
			'variables' => array('devicetypes' => NULL, 'pageCount' => NULL, 'pageNumber' => NULL),
			'template' => 'flowadmin.devicetypes.maincontent',
			'path' => drupal_get_path('module', 'flowadmin') . "/themes",
		),

		'flowadmin_devicetypes_btn_panel'  => array(
			'variables' => array('devicetypesID' => NULL),
			'template' => 'flowadmin.devicetypes.btn_panel',
			'path' => drupal_get_path('module', 'flowadmin') . "/themes",
		),			
	
	);
	
	return $items;
}


function flowadmin_generate_devicetypes_page()
{
	global $user;
	$htmlOutput = null;
	
	flowadmin_access();
	
	try {
			$pageNumber = func_get_arg(0);
			$pageNumber = (isset($pageNumber)) ? $pageNumber : 1;
			$pageSize = 10;
			$oauthInfo = flowautho_get_oauth_credentials($user->mail);
			$deviceTypesServices = new FDWDeviceTypeServicesImpl($oauthInfo, $user);
			$deviceTypesContainer = $deviceTypesServices->getDeviceTypes($pageNumber, $pageSize);
			$deviceTypes = $deviceTypesContainer['items'];
			
			//drupal_set_message('<pre>[flowadmin_generate_devicetypes_page:: ] DeviceTypes:: '. print_r($deviceTypes, true).'</pre>');
			$addURL = base_path() . FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES.'/'.FLOWADMIN_ADD;
			
			$headerLeft = '';
			$headerRight = theme('flowadmin_devicetypes_headerright', array('url' => $addURL));
			$contentArgs =  array('devicetypes' => $deviceTypes, 'pageCount' => $deviceTypesContainer['pagecount'], 'pageNumber' => $pageNumber);
			$mainContent = theme('flowadmin_devicetypes_maincontent', $contentArgs);
				
			$htmlOutput =  theme('flowautho_dashboard_content', array('headerLeft' => $headerLeft, 
													  'headerCenter' => t('Device Types'),  
													  'headerRight' => $headerRight, 
													  'mainContent' => $mainContent));	
		
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceTypeServicesImpl error:: '. print_r($e->getMessage(),true));
	}		
	
	return $htmlOutput;
}

function flowadmin_generate_add_devicetype_page()
{
	global $user;
	$deviceTypeID = func_get_arg(0);
	
	flowadmin_access();
	
	$deviceTypeForm = drupal_get_form('flowadmin_devicetype_form', $deviceTypeID);
	
	$headerLeft = '';
	$headerRight = '';
	$mainContent = drupal_render($deviceTypeForm);
	$pageTitle = (isset($deviceTypeID)) ? t('Edit Device Type') : t('Add Device Type') ;
		
	$htmlOutput =  theme('flowautho_dashboard_content', array('headerLeft' => $headerLeft, 
											  'headerCenter' => $pageTitle,  
											  'headerRight' => $headerRight, 
											  'mainContent' => $mainContent));

	return $htmlOutput;
}

function flowadmin_devicetype_form($form, &$form_state, $deviceTypeID=null)
{
	global $user;
	$deviceType = null;
	$form = array();
	
	if (isset($deviceTypeID)) 
	{
		/**
		 * We are in edit mode. so load the device type to be edited
		 */
		try {
				$oauthInfo = flowautho_get_oauth_credentials($user->mail);
				$deviceTypesServices = new FDWDeviceTypeServicesImpl($oauthInfo, $user);
				$deviceType = $deviceTypesServices->getDeviceType($deviceTypeID);
		} catch (FDWUnknownUserException $e) {
			watchdog('error', 'FDWDeviceTypeServicesImpl error:: '. print_r($e->getMessage(),true));
		}			
	}
	
	if (!isset($deviceType)) 
	{
		$deviceType = array('DeviceTypeID'=>'', 'Name'=>'', 'DevName'=>'', 'IsManageable'=>false, 'MACAddressPattern'=>'');
	}
	
	$form['deviceid'] = array(
		'#type' => 'hidden',
		'#value' =>$deviceTypeID,
	);

	$form['name'] = array(
	  '#type' => 'textfield', 
	  '#title' => 'Name',
	  '#maxlength' => 50,
	  '#required' => TRUE,
	  '#attributes' => array('class' => array('c-ate-devicetype-form-name')),
	  '#default_value' => $deviceType['Name'], 
	 
	);	
	
	$form['devname'] = array(
	   '#type' => 'textfield', 
	   '#title' => 'DevName',
	   '#description' => t('A codename to internally identify the device type wthin your organisation'),	
	   '#maxlength' => 50,
	   '#required' => TRUE,
	   '#attributes' => array('class' => array('c-ate-devicetype-form-devname')),
	   '#default_value' => $deviceType['DevName'],  
	);
	
	$form['macaddress_pattern'] = array(
	   '#type' => 'textfield', 
	   '#title' => 'Mac Address Pattern',
	   '#description' => t('an SQL LIKE style mac address pattern e.g XQT564% '),	
	   '#maxlength' => 70,
	   '#required' => FALSE,
	   '#attributes' => array('class' => array('c-ate-devicetype-form-macaddress-pattern')),
	   '#default_value' => $deviceType['MACAddressPattern'],  
	);		
	
	$form['ismanaged'] = array(
	   '#type' => 'checkbox', 
	   '#title' => 'Supports Creator',
	   '#description' => t('A device of this type will be able to use Creator'),	
	   '#attributes' => array('class' => array('c-ate-devicetype-form-ismanaged')),
	   '#default_value' => $deviceType['IsManageable'],  
	);	
		
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
		'#attributes' => array('class' => array('c-ate-devicetype-form-submit-btn')),
	);	

	$prefixe = '<div class="row c-ate-devicetype-form c-devicetype-form-wrapper">'
			 . '	<div class="col-xs-12 col-sm-5 col-lg-4">';
	$suffix  = '	</div>'
			 . '</div>';
		
	$form['#prefix'] = $prefixe;
	$form['#suffix'] = $suffix;	
	
		
	return $form;
}

function flowadmin_devicetype_form_validate($form, &$form_state)
{
	
}

function flowadmin_devicetype_form_submit($form, &$form_state)
{
	global $user;
	
	$deviceID = $form_state['values']['deviceid'];
	$name = $form_state['values']['name'];
	$devName = $form_state['values']['devname'];
	$macAddressPattern = $form_state['values']['macaddress_pattern'];
	$isManaged = ($form_state['values']['ismanaged'] != 0) ? true : false;
	
	try {
			$oauthInfo = flowautho_get_oauth_credentials($user->mail);
			$deviceTypesServices = new FDWDeviceTypeServicesImpl($oauthInfo, $user);
				
			if (isset($deviceID)) 
			{
				/**
				 * Update Existing device
				 */
				if ($deviceTypesServices->updateDeviceType($deviceID, $name, $devName, $isManaged, $macAddressPattern)) 
				{
					//$path = FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES;
					$msg = t('Your new device type was successfully updated.');
					flowautho_set_message('c-ate-update-devicetype-success', $msg, 'status', true);
					drupal_goto(FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES.'/1');					
				}
				else
				{
					$msg = t('Sorry an error occured while trying to update your device type.');
					flowautho_set_message('c-ate-update-devicetype-error', $msg, 'error', false);					
				}
			}
			else
			{
				/**
				 * Insert new device
				 */
				if ($deviceTypesServices->createDeviceType($name, $devName, $isManaged, $macAddressPattern)) 
				{
					//$path = FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES;
					$msg = t('Your new device type was successfully created.');
					flowautho_set_message('c-ate-add-devicetype-success', $msg, 'status', true);
					drupal_goto(FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES.'/1');
				}
				else
				{
					$msg = t('Sorry an error occured while trying to create your new device type.');
					flowautho_set_message('c-ate-add-devicetype-error', $msg, 'error', false);					
				}
			}
			
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceTypeServicesImpl error:: '. print_r($e->getMessage(),true));
	}		

}

/**
 * Delete a device type
 * 
 */
function flowadmin_delete_devicetype()
{
	global $user;	
	$deviceTypeId = func_get_arg(0);
	
	flowadmin_access();
	
	try {
			$oauthInfo = flowautho_get_oauth_credentials($user->mail);
			$deviceTypesServices = new FDWDeviceTypeServicesImpl($oauthInfo, $user);
				
			if (isset($deviceTypeId)) 
			{
				if ($deviceTypesServices->deleteDeviceTypeByID($deviceTypeId)) 
				{
					$msg = t('Your device type was successfully deleted.');
					flowautho_set_message('c-ate-delete-devicetype-success', $msg, 'status', true);
					drupal_goto(FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES.'/1');					
				}
				else
				{
					$msg = t('Sorry an error occrured when we tried to delete your device type.');
					flowautho_set_message('c-ate-delete-devicetype-error', $msg, 'error', true);
					drupal_goto(FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES.'/1');					
				}
			}
			
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceTypeServicesImpl error:: '. print_r($e->getMessage(),true));
	}	
	
}
