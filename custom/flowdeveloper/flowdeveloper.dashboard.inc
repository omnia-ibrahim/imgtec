<?php
/**
 * @file
 * This file contains the function definitions for dashboard
 */

//module_load_include('inc', 'user', 'user.pages');

define('FDW_DASHBOARD', 'dashboard');
define('FDW_METRICSDASHBOARD', 'metrics');
define('FDW_LOGS', 'logs');

function _flowdeveloper_menu_dashboard()
{
	$items = array();

	$items[FDW_DASHBOARD] = array(
		'title' => t('Dashboard'),
		'description' => t('Dashboard for Flow Developer website'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowdeveloper_generate_dashboard_pages',
		'type' => MENU_NORMAL_ITEM,
		'menu_name' => 'user-menu',
		'weight' => 1,
	);
	
	$items[FDW_DASHBOARD .'/'. FDW_AJAX .'/'. FLOWDEVEL_REG_DEVICES_BYTYPE] = array(
	
		'title' => t('Registered devices by type'),
		'description' => t('Retrieve registered devices by type'),
		'access callback' => TRUE,
		'page callback' => 'flowdeveloper_db_ajax_get_registered_devices_by_type_metrics',
		'type' => MENU_CALLBACK,	
		'weight' => -72,
	);

	$items[FDW_DASHBOARD .'/'. FDW_AJAX .'/'. FLOWDEVEL_CONNECTED_DEVICES] = array(
	
		'title' => t('Connected devices'),
		'description' => t('Retrieve connected devices metrics for the past month'),
		'access callback' => TRUE,
		'page callback' => 'flowdeveloper_db_ajax_get_connected_devices_for_a_month',
		'type' => MENU_CALLBACK,	
		'weight' => -72,
	);	
	
	$items[FDW_DASHBOARD .'/'. FDW_AJAX .'/'. FLOWDEVEL_DEVICES_BY_FIRMWARE] = array(
	
		'title' => t('Devices by Firmware versions'),
		'description' => t('Retrieve metrics for the number of devices running a particular firmware version'),
		'access callback' => TRUE,
		'page callback' => 'flowdeveloper_db_ajax_get_firmware_versionsmetrics',
		'type' => MENU_CALLBACK,	
		'weight' => -72,
	);

	$items[FDW_DASHBOARD .'/'. FDW_AJAX .'/'. FLOWDEVEL_DEVICES_BANDWIDTH] = array(
	
		'title' => t('Device Bandwidth '),
		'description' => t('Retrieve metrics for device bandwidth usage for the last month'),
		'access callback' => TRUE,
		'page callback' => 'flowdeveloper_db_ajax_get_device_bandwidth_metrics',
		'type' => MENU_CALLBACK,	
		'weight' => -72,
	);
	

	$items[FDW_DASHBOARD .'/'. FDW_AJAX .'/'.  FLOWDEVEL_DRILL_DOWN .'/'. FLOWDEVEL_DEVICES_BANDWIDTH] = array(
	
		'title' => t('Device Bandwidth drilldown '),
		'description' => t('Retrieve metrics for device bandwidth for drilldown'),
		'access callback' => TRUE,
		'page callback' => 'flowdeveloper_db_dd_ajax_get_device_bandwidth_metrics',
		'type' => MENU_CALLBACK,	
		'weight' => -72,
	);	

	$items[FDW_DASHBOARD .'/'. FDW_AJAX .'/'.  FLOWDEVEL_DRILL_DOWN .'/'. FLOWDEVEL_CONNECTED_DEVICES] = array(
	
		'title' => t('Connected devices drilldown '),
		'description' => t('Retrieve metrics for connected devices for drilldown'),
		'access callback' => TRUE,
		'page callback' => 'flowdeveloper_db_dd_ajax_get_connected_devices_metrics',
		'type' => MENU_CALLBACK,	
		'weight' => -72,
	);	
	

	$items[FDW_DASHBOARD .'/'. FDW_AJAX .'/'.  FLOWDEVEL_DRILL_DOWN .'/'. FLOWDEVEL_FIRMWARE_VERSIONS] = array(
	
		'title' => t('Firmware Versions breakdown by device types'),
		'description' => t('Firmware Versions breakdown by device types for drilldown'),
		'access callback' => TRUE,
		'page callback' => 'flowdeveloper_db_dd_ajax_get_firmware_versions_by_devicetypes',
		'type' => MENU_CALLBACK,	
		'weight' => -72,
	);	


	$items[FDW_DASHBOARD .'/'. FDW_METRICSDASHBOARD ] = array(
		'title' => t('Metrics'),
		'description' => t('Metrics Dashboard for Flow Developer website'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowdeveloper_generate_metrics_dashboard_pages',
		'type' => MENU_NORMAL_ITEM,
		'menu_name' => 'user-menu',
		'weight' => 1,
	);

	$items[FDW_DASHBOARD .'/user/%user/edit'] = array(
		'title' => t('Update Profile'),
		'description' => t('Update user profile'),
	//	'access callback' => 'user_is_logged_in',
                'access callback' => 'user_edit_access',
                'access arguments' => array(2),
		'page callback' => 'flowdeveloper_generate_user_profile_edit_pages',
		'page arguments' => array(2),
		'type' => MENU_NORMAL_ITEM,
		//'menu_name' => 'user-menu',
		'weight' => 1,
	);

	$items[FDW_DASHBOARD .'/'. FDW_LOGS . '/%/%'] = array(
		'title' => t('Logs'),
		'description' => t('View Log messages from your devices'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowdeveloper_generate_logs_page',
		'page arguments' => array(2, 3),
		'type' => MENU_NORMAL_ITEM,
		'menu_name' => 'user-menu',
		'weight' => 1,
	);



	return $items;
}

function flowdeveloper_generate_dashboard_pages()
{
	drupal_goto(FDW_DASHBOARD.'/'.FDW_DEVICES);
	//drupal_set_title("Dashboard Home"); //no title please
	//return theme('flowdeveloper_dashboard_main');

	/*$output = '<p>This is the Dashboard homepage. It will feature an overview of your account and devices information</p><br>';
	$output .= '<p><a href="dashboard/metrics">Metrics</a></p>';
	$output .= '<p><a href="dashboard/devices">Devices</a></p>';
	$output .= '<p><a href="dashboard/msgviewer">Message Viewer</a></p>';
	return $output;*/
}

function flowdeveloper_generate_metrics_dashboard_pages()
{

	//return theme('flowdeveloper_temporary_metrics_placeholder');

	$registeredDevices = theme('flowdeveloper_dashboard_registered_devices', array('regDevicesMetrics' => flowdeveloper_db_get_registered_devices_metrics()));
	$registeredDevicesByType = theme('flowdeveloper_dashboard_registered_devices_by_type', array('regDevicesMetrics' => null));
	$connectedDevices = theme('flowdeveloper_dashboard_connected_devices', array('connDevicesMetrics' => null));
	$deviceBandWidth = theme('flowdeveloper_dashboard_connected_devices_bandwidth_metrics', array('deviceBandwidthMetrics' => null));
	
	if (flowdeveloper_is_licensee_admin()) 
	{
		$firmwareVersionsCount = theme('flowdeveloper_dashboard_firmware_device_count', array('firmwareCountMetrics' => null));
		$devicesByFirmware =  theme('flowdeveloper_dashboard_devices_by_firmware', array('firmwareDeviceMetrics' => null));		

		$output = '<div class="c-dashboard-canvas container-fluid clearfix">'
				. '	<div class="row">'
				. 		$registeredDevices
				.		$registeredDevicesByType				
				. '	</div>'
				. '	<div class="row">'
				. 		$connectedDevices
				. '	</div>'
				. '	<div class="row">'
				. 		$firmwareVersionsCount
				. 		$devicesByFirmware				
				. '	</div>'
				. '	<div class="row">'
				.		$deviceBandWidth				
				. '	</div>'				
				. '</div>';
	}
	else
	{
		$output = '<div class="c-dashboard-canvas container-fluid clearfix">'
				. '	<div class="row">'
				. 		$registeredDevices
				.		$registeredDevicesByType				
				. '	</div>'
				. '	<div class="row">'
				. 		$connectedDevices
				. '	</div>'
				. '	<div class="row">'
				.		$deviceBandWidth				
				. '	</div>'				
				. '</div>';				
	}

	
//	return $output;
  
  return theme('flowautho_dashboard_content', array('headerLeft' => '', 
					       	  'headerCenter' => t('Metrics'),  
					 	  'headerRight' => '', 
						  'mainContent' => $output));	

}

/**
 * Return a list of device types available tot the user
 * 
 * @return array
 */
function flowdeveloper_db_get_devicetype_list()
{
	global $user;
	$oauthInfo = flowautho_get_oauth_credentials($user->mail);
	$deviceTypeList = null;
	$tempDTL = null;
	
	try {
		
		$deviceManServices = new FDWDeviceManagementServicesImpl($oauthInfo, $user);
		if (flowdeveloper_is_licensee_admin()) 
		{
			$tempDTL = $deviceManServices->getLicenseeDeviceTypes();
		}
		else
		{
			$tempDTL = $deviceManServices->getDeviceTypes();
		}
		
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWMetricsServicesImpl error:: '. print_r($e->getMessage(),true));
	}	
	
	if ($tempDTL) 
	{
		foreach ($tempDTL as $dt) 
		{
			$deviceTypeList[] = $dt['Name'];
		}
	}
	
	//_flowautho_debug('[flowdeveloper_db_get_devicetype_list::] DeviceTypes:: ' .print_r($deviceTypeList, true));
	
	return $deviceTypeList;
}


/**
 * Returns the registered devices metrics for the dashboard
 * 
 * @return array
 */
function flowdeveloper_db_get_registered_devices_metrics()
{
	global $user;
	$rdmetrics =  null;
	$oauthInfo = flowautho_get_oauth_credentials($user->mail);
	
	try {
		
		
		//Create a metrics services object
		$metricsServices = new FDWMetricsServicesImpl($oauthInfo, $user);
		if (flowdeveloper_is_licensee_admin()) 
		{
			$rdmetrics = $metricsServices->getDevices(true);
		}
		else
		{
			$rdmetrics = $metricsServices->getDevices(false);
		}
		
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWMetricsServicesImpl error:: '. print_r($e->getMessage(),true));
	}	
	
	return $rdmetrics;
}


/**
 * Return registered device metrics grouped by device type
 * 
 */
function flowdeveloper_db_get_registered_devices_by_type_metrics()
{
	global $user;
	$rdmetrics =  null;
	$oauthInfo = flowautho_get_oauth_credentials($user->mail);
	
	try {
		
		//Create a metrics services object
		$metricsServices = new FDWMetricsServicesImpl($oauthInfo, $user);
		if (flowdeveloper_is_licensee_admin()) 
		{
			$rdmetrics = $metricsServices->getDevicesByType(true);	
		}
		else
		{
			$rdmetrics = $metricsServices->getDevicesByType(false);
		}
		
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWMetricsServicesImpl error:: '. print_r($e->getMessage(),true));
	}	

	return $rdmetrics;
}

function flowdeveloper_db_ajax_get_registered_devices_by_type_metrics()
{
	$rdmetrics = flowdeveloper_db_get_registered_devices_by_type_metrics();
	$ajaxResponse = array('error' => 1, 'metrics' => array());
	if (is_array($rdmetrics)) 
	{
		$ajaxResponse = array('error' => 0, 'metrics' => $rdmetrics);
	}
	return drupal_json_output($ajaxResponse);
}

/**
 * Return connected devices metrics for the last month
 * 
 * @return array
 */
function flowdeveloper_db_get_connected_devices_for_a_month()
{
	global $user;
	$oauthInfo = flowautho_get_oauth_credentials($user->mail);	
	$cdmetrics = null;
	
	$tempDataContainer = Array();
	$counter=30;
	$newStartDate = new DateTime('now');
	for ($i = 1; $i <= $counter; $i++) 
	{
		if ($i > 1) 
		{
			$tempToday = $newStartDate->sub(new DateInterval('P1D'));
		}
		else
		{
			$tempToday = $newStartDate;
		}
		
		$index = $tempToday->format('d_M');
		$tempDataContainer[$index] = array('date' => $tempToday->format('d M'), 'connected' => 0);
	}	
	
	try {
		
		$metricsServices = new FDWMetricsServicesImpl($oauthInfo, $user);
		$startDate = new DateTime('now');
		$startDate->sub(new DateInterval('P30D'));
		$endDate = new DateTime('now');
		$tempCDmetrics = null;
		
		if (flowdeveloper_is_licensee_admin()) 
		{
			$tempCDmetrics = $metricsServices->getConnectedDevicesOverTime($startDate->format('Y-m-d'), $endDate->format('Y-m-d'), true);	
		}
		else
		{
			$tempCDmetrics = $metricsServices->getConnectedDevicesOverTime($startDate->format('Y-m-d'), $endDate->format('Y-m-d'));
		}
		
		if ($tempCDmetrics && is_array($tempCDmetrics)) 
		{
			foreach ($tempCDmetrics as $key => $cdm) 
			{
				if (array_key_exists($key, $tempDataContainer)) 
				{
					$date = new DateTime($cdm['date']);
					$tempDataContainer[$key] = array('date' => $date->format('d M'), 'connected' => $cdm['connected']);
				}
			}
		}
		
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWMetricsServicesImpl error:: '. print_r($e->getMessage(),true));
	}		

	$cdmetrics = array_reverse($tempDataContainer);
	
	return  $cdmetrics;
}

function flowdeveloper_db_ajax_get_connected_devices_for_a_month()
{
	$cdmetrics = flowdeveloper_db_get_connected_devices_for_a_month();
	$ajaxResponse = array('error' => 1, 'metrics' => array());
	if (is_array($cdmetrics)) 
	{
		$ajaxResponse = array('error' => 0, 'metrics' => $cdmetrics, 'devicetypes' => flowdeveloper_db_get_devicetype_list());
	}
	return drupal_json_output($ajaxResponse);	
}

function flowdeveloper_db_get_firmware_versionsmetrics()
{
	global $user;
	$devicesByFirmware = null;
	$metricsInfo = null;
	
	try {
		
		$oauthInfo = flowautho_get_oauth_credentials($user->mail);
		//Create a metrics services object
		$metricsServices = new FDWMetricsServicesImpl($oauthInfo, $user);
		if (flowdeveloper_is_licensee_admin()) 
		{
			$devicesByFirmware = $metricsServices->getFirmwareVersions();
			if (isset($devicesByFirmware)) 
			{
				$metricsInfo = array(
					'fwcount' => $devicesByFirmware['firmwarecount'], 
					'fbydevicetype' => $devicesByFirmware['firmware_by_devicetypes']
				);
			}	
		}
	
		
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWMetricsServicesImpl error:: '. print_r($e->getMessage(),true));
	}		
	
	return  $metricsInfo;
	
}

function flowdeveloper_db_ajax_get_firmware_versionsmetrics()
{
	$dbfwMetrics = flowdeveloper_db_get_firmware_versionsmetrics();	
	$ajaxResponse = array('error' => 1, 'metrics' => array());
	if (is_array($dbfwMetrics)) 
	{
		$ajaxResponse = array('error' => 0, 'metrics' => $dbfwMetrics);
	}	
	
	return drupal_json_output($ajaxResponse);		
}

function flowdeveloper_db_get_connected_devices_metrics_by_period($startDate, $endDate, $deviceTypes)
{
	$sd = clone $startDate;
	$ed = clone $endDate;	
	
	$sdDiff = clone $startDate;
	$edDiff = clone $endDate;	
	
	$ddiff = $sdDiff->diff($edDiff);
	$dayCount = $ddiff->format('%a');

	$metricsDataByDeviceType = array();
	$finalMetricsContainer = array();

	/**
	 * build data container with dates as keys
	 */
	if (isset($deviceTypes) && (strlen($deviceTypes) > 0)) 
	{
		$metricsContainer = flowdeveloper_db_get_empty_data_container(clone $endDate, $dayCount);		
		$defaultValues = null;
		$dtContainer = explode(',', $deviceTypes);
		foreach ($dtContainer as $dt) 
		{
			$defaultValues[$dt] = 0;
		}
		
		/**
		 * prime each date in the default array  with default values for each selected device type
		 */
		foreach ($metricsContainer as $date => $defaultValue) 
		{
			$metricsContainer[$date] = $defaultValues;
		}

		/**
		 * Retrieve metrics data for the period in question
		 */
		$metrics = Lounge2::get_instance()->get_metrics();
		if (!$metrics->is_empty_object()) 
		{
			$lm = $metrics->get_licensee_metrics();
			$regDevicesMetrics = $lm->get_registered_devices_by_devicetype();
			if (!$regDevicesMetrics->is_empty_object()) 
			{
				//$i =0;
				$pageSize = ($dayCount > 30) ? $dayCount : 30;
				foreach ($regDevicesMetrics as $dtm) 
				{
					$dtName = $dtm->Name;
					if (in_array($dtName, $dtContainer)) 
					{
						$metricsByDays = $dtm->get_connected_devices_metrics_by_days($sd->format('Y-m-d'), $ed->format('Y-m-d'), 0, $pageSize);
						if (!$metricsByDays->is_empty_object()) 
						{
							$tempDeviceTypeMetrics = array();
							foreach ($metricsByDays as $mi) 
							{
								$date = new DateTime($mi->Date);
								$index = $date->format('d_M_Y');
								if (array_key_exists($index, $metricsContainer)) 
								{
									$metricsContainer[$index][$dtName] = $mi->Total;
								}
							}
						} 
					}
				}
			}
		}

		/**
		 * transform metrics container
		 */
		$transformedMetricsContainer = array();
		foreach ($metricsContainer as $date => $mData) 
		{
			$tempDTMContainer = array(); //metrics by device types
			foreach ($mData as $dtName => $totalConnected) 
			{
				$tempDTMContainer[] = array('devicetype' => $dtName, 'connected' => $totalConnected);
			}
			
			$transformedMetricsContainer[] = array('date' => $date, 'data' => $tempDTMContainer);
		}
		
		$finalMetricsContainer = array('devicetypes' => $dtContainer, 'metricsdata' => $transformedMetricsContainer); 
		
	}	
	else
	{

			// just retrieve bandwidth metrics using only dates;
		$dtContainer = null;
		/**
		 * Setting default values
		 */
		//$newStartDate = new DateTime($endDate);
		$newStartDate = clone $endDate;
		for ($i = 0; $i <= $dayCount; $i++) 
		{
			if ($i >= 1) 
			{
				$tempToday = $newStartDate->sub(new DateInterval('P1D'));
			}
			else
			{
				$tempToday = $newStartDate;
			}		
			$index = $tempToday->format('d_M_Y');
			$metricsContainer[$index] = array('date' => $tempToday->format('d M'), 'connected' => 0);
		}		
		
		/**
		 * Retrieve metrics data for the period in question
		 */
		$metrics = Lounge2::get_instance()->get_metrics();
		if (!$metrics->is_empty_object()) 
		{
			$lm = $metrics->get_licensee_metrics();
			$connectedMetrics = $lm->get_devices_connected_over_time();
			if ((!$connectedMetrics->is_empty_object()) && ($connectedMetrics instanceof Lounge2_MetricMonthSummary)) 
			{
				$pageSize = ($dayCount > 30) ? $dayCount : 30;
				$metricsByDays = $connectedMetrics->get_metrics_by_days($sd->format('Y-m-d'), $ed->format('Y-m-d'), 0, $pageSize);
				if (!$metricsByDays->is_empty_object()) 
				{
					foreach ($metricsByDays as $mi) 
					{
						$date = new DateTime($mi->Date);
						$index = $date->format('d_M_Y');
						if (array_key_exists($index, $metricsContainer)) 
						{
							$metricsContainer[$index] = array('date' => $date->format('d M'), 'connected' => $mi->Total);
						}
					}
				} 
			}
		}
		
		/**
		 * transform metrics container
		 */
		$transformedMetricsContainer = array();
		foreach ($metricsContainer as $date => $mData) 
		{
			$transformedMetricsContainer[] = $mData;
		}		
		
		$finalMetricsContainer = array('devicetypes' => 'none', 'metricsdata' => array_reverse($transformedMetricsContainer)); 		
	}
	
	//_flowautho_debug('[flowdeveloper_db_get_connected_devices_metrics_by_period::] TransformedMetricsContainer: '. print_r($finalMetricsContainer, true));
		
	return $finalMetricsContainer;	
}

function flowdeveloper_db_dd_ajax_get_connected_devices_metrics()
{
	$deviceTypes = $_POST['_devicetypes'];
	$period = $_POST['_period'];
	$conDevicesMetrics = null;
	
	if ($period == 'month') 
	{
		$startDate = new DateTime('now');
		$startDate->sub(new DateInterval('P30D'));
		$endDate = new DateTime('now');
	}
	else
	{
		$startDate = new DateTime('now');
		$startDate->sub(new DateInterval('P1Y'));
		//$startDate->sub(new DateInterval('P3M'));
		$endDate = new DateTime('now');		
	}

	/**
	_flowautho_debug('[flowdeveloper_db_dd_ajax_get_device_bandwidth_metrics::] startDate: '. $startDate);	
	_flowautho_debug('[flowdeveloper_db_dd_ajax_get_device_bandwidth_metrics::] endDate: '. $endDate);
	_flowautho_debug('[flowdeveloper_db_dd_ajax_get_device_bandwidth_metrics::] deviceTypes: '. $deviceTypes);
	_flowautho_debug('[flowdeveloper_db_dd_ajax_get_device_bandwidth_metrics::] Period: '. $period);
	**/
		
	if (flowdeveloper_is_licensee_admin()) 
	{
		//$conDevicesMetrics = flowdeveloper_db_get_connected_devices_metrics_by_period($startDate, $endDate, $deviceTypes);
	}
	else
	{
		//$conDevicesMetrics = flowdeveloper_db_user_get_connected_devices_metrics_by_period($startDate, $endDate, $deviceTypes);
	}
	
	$ajaxResponse = array('error' => 1, 'metrics' => array());
	if (is_array($conDevicesMetrics)) 
	{
		$ajaxResponse = array('error' => 0, 'metrics' => $conDevicesMetrics, 'devicetypes' => flowdeveloper_db_get_devicetype_list());
	}	
	
	return drupal_json($ajaxResponse);		
}

function flowdeveloper_db_get_empty_data_container(DateTime $startDate, $dayCount)
{
	$datesContainer = array();
	
	if (isset($startDate) && isset($dayCount)) 
	{
		$tempDates = array();
		for ($i = 0; $i <= $dayCount; $i++) 
		{
			if ($i >= 1) 
			{
				$tempToday = $startDate->sub(new DateInterval('P1D'));
			}
			else
			{
				$tempToday = $startDate;
			}		
			$tempDates[] = $tempToday->format('d_M_Y');
		}
		
		$reversedDates = array_reverse($tempDates);
		foreach ($reversedDates as $date) 
		{
			$datesContainer[$date] = array();
		}
	}

	return $datesContainer;
}

function flowdeveloper_db_get_device_bandwidth_metrics()
{
	global $user;
	$oauthInfo = flowautho_get_oauth_credentials($user->mail);	
	$dbmetrics = array();
	
	$tempDataContainer = Array();
	$counter=30;
	$newStartDate = new DateTime('now');
	for ($i = 1; $i <= $counter; $i++) 
	{
		if ($i > 1) 
		{
			$tempToday = $newStartDate->sub(new DateInterval('P1D'));
		}
		else
		{
			$tempToday = $newStartDate;
		}		
		$index = $tempToday->format('d_M');
		$tempDataContainer[$index] = array('date' => $tempToday->format('d M'), 'bandwidth' => 0);
	}

	try {
		
		$metricsServices = new FDWMetricsServicesImpl($oauthInfo, $user);
		$startDate = new DateTime('now');
		$startDate->sub(new DateInterval('P30D'));
		$endDate = new DateTime('now');
		$tempDBmetrics = null;
		
		if (flowdeveloper_is_licensee_admin()) 
		{
			$tempDBmetrics = $metricsServices->getDeviceBandwidthUsage($startDate->format('Y-m-d'), $endDate->format('Y-m-d'), true);	
		}
		else
		{
			$tempDBmetrics = $metricsServices->getDeviceBandwidthUsage($startDate->format('Y-m-d'), $endDate->format('Y-m-d'));
		}
		
		
		if ($tempDBmetrics && is_array($tempDBmetrics)) 
		{
			foreach ($tempDBmetrics as $key => $dbm) 
			{
				if (array_key_exists($key, $tempDataContainer)) 
				{
					$date = new DateTime($dbm['date']);
					$tempDataContainer[$key] = array('date' => $date->format('d M'), 'bandwidth' => $dbm['bandwidth']);
				}
			}
		}
		
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWMetricsServicesImpl error:: '. print_r($e->getMessage(),true));
	}	
		
	$dbmetrics = array_reverse($tempDataContainer);
	
	return  $dbmetrics;
}


function flowdeveloper_db_ajax_get_device_bandwidth_metrics()
{
	$dbmetrics = flowdeveloper_db_get_device_bandwidth_metrics();
	$ajaxResponse = array('error' => 1, 'metrics' => array());
	if (is_array($dbmetrics)) 
	{
		$ajaxResponse = array('error' => 0, 'metrics' => $dbmetrics, 'devicetypes' => flowdeveloper_db_get_devicetype_list());
	}
	return drupal_json_output($ajaxResponse);	
}

/**
 *
 */
function flowdeveloper_generate_user_profile_edit_pages($userID) {
//$account = user_load ($userID);

  $profile_form = drupal_get_form('user_profile_form', $userID);
  $mainContent = drupal_render($profile_form);

  return theme('flowautho_dashboard_content', array('headerLeft' => '', 
	        				  'headerCenter' =>  t('Update user profile'),  
			                          'headerRight' => '', 
                                                  'mainContent' => $mainContent));	

  //return theme('flowdeveloper_user_profile_form');
}

function flowdeveloper_generate_logs_page($logType, $pageNumber)
{
	global $user;
	$oauthInfo = flowautho_get_oauth_credentials($user->mail);
	$pageSize = 3;
	$logEntries = null;
	$output = '<p>There are currently no log entries available for your selected log type</p>';
	$pageNumber = (isset($pageNumber)) ? $pageNumber : 1;
	
	
	try {
		
		$loggingServices = new FDWLoggingServicesImpl($oauthInfo, $user);
		$logEntries = $loggingServices->getLogEntriesByType($logType, $pageNumber, $pageSize);
		//drupal_set_message('<pre>Logs:: '.print_r($logEntries, true).'</pre>');
   
		$selectForm = drupal_get_form('flowdeveloper_form_logs', $logType);
		$themeArgs = array(
			'logType' => $logType, 
			'logData' => $logEntries['logs'], 
			'pageCount' => $logEntries['pagecount'],
			'currentPage' => $pageNumber, 
			'logTypeForm' => $selectForm,
			'pageSize' => $pageSize
		);
		$output =  theme('flowdeveloper_logs_viewer', $themeArgs);
	
		
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWLoggingServicesImpl error:: '. print_r($e->getMessage(),true));
	}

	return $output;
}

function flowdeveloper_form_logs($form, &$form_state, $logType)
{
	global $user;
	
	$oauthInfo = flowautho_get_oauth_credentials($user->mail);
	$form = array();
	
	try {
		
			$loggingServices = new FDWLoggingServicesImpl($oauthInfo, $user);
			$logs = $loggingServices->getLogTypes();
			//$logTypes[FDWLoggingServicesImpl::ALL_LOGS] = FDWLoggingServicesImpl::ALL_LOGS;
			foreach ($logs as $log) 
			{
				$name = $log['Name'];
				$logTypes[$name] = $name;
			}
			
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWLoggingServicesImpl error:: '. print_r($e->getMessage(),true));
	}
	
	$form['log_type'] = array(
		'#type' => 'select',
		'#title' => 'Log Types',
		'#description' => 'Select a log type to view the entries.',
		'#options' => $logTypes,
		'#default_value' => $logType, 
		'#required' => TRUE,
		'#attributes' => array('class' => array('c-ate-logtype')),
		'#weight' => 1,
	);
	
	return $form;
}

function flowdeveloper_form_logs_submit($form, &$form_state)
{
	$logType = $form_state['values']['log_type'];
	drupal_goto(FDW_DASHBOARD .'/'. FDW_LOGS . '/'. $logType .'/1');
}
