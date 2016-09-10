<?php

/**
 * @file
 * This file contains all themeable objects defined by the flowdeveloper module
 */

/**
 * Implements hook_theme()
 */
function flowdeveloper_theme($existing, $type, $theme, $path)
{
	$themes = array(
	
		'flowdeveloper_link'  => array(
			'variables' => array('content' => NULL, 'path' => NULL, 'qualifier' => NULL, 'isHtml' => false),
			'function' => 'theme_flowdeveloper_link',
			'file' => 'flowdeveloper.theme.inc',
		),

		'flowdeveloper_homepage' => array(
			'variables' => array(),
		),
		
		'flowdeveloper_user_registration' => array(
			'variables' => array(),
			'function' => 'theme_flowdeveloper_user_registration',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes",
			'file' => 'flowdeveloper.theme.user.inc',		
		),

		'flowdeveloper_licensee_list' => array(
			'variables' => array('licensees' => NULL),
			'function' => 'theme_flowdeveloper_licensee_list',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes",
			'file' => 'flowdeveloper.theme.licensee.inc',		
		),

		'flowdeveloper_footer' => array(
			'template' => 'flowdeveloper.footer',
			'path' => drupal_get_path('module', 'flowdeveloper') . '/themes/templates',
			'type' => 'theme',
			'variables' => array(
				'content' => NULL,
			),
		),
		
		'flowdeveloper_dashboard_registered_devices'  => array(
			'variables' => array('regDevicesMetrics' => NULL),
			'template' => 'fdw-metrics-registereddevices',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes",
			'file' => 'flowdeveloper.theme.dashboard.inc',		
		),	

		'flowdeveloper_dashboard_registered_devices_by_type'  => array(
			'variables' => array('regDevicesMetrics' => NULL),
			'function' => 'theme_flowdeveloper_db_registered_devices_by_type',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes",
			'file' => 'flowdeveloper.theme.dashboard.inc',		
		),	

		'flowdeveloper_dashboard_connected_devices'  => array(
			'variables' => array('connDevicesMetrics' => NULL),
			'function' => 'theme_flowdeveloper_db_connected_devices',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes",
			'file' => 'flowdeveloper.theme.dashboard.inc',		
		),
		
		'flowdeveloper_dashboard_firmware_device_count'  => array(
			'variables' => array('firmwareCountMetrics' => NULL),
			'function' => 'theme_flowdeveloper_db_firmware_device_count',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes",
			'file' => 'flowdeveloper.theme.dashboard.inc',		
		),			

		'flowdeveloper_dashboard_devices_by_firmware'  => array(
			'variables' => array('firmwareDeviceMetrics' => NULL),
			'function' => 'theme_flowdeveloper_db_devices_by_firmware',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes",
			'file' => 'flowdeveloper.theme.dashboard.inc',		
		),	

		'flowdeveloper_dashboard_connected_devices_bandwidth_metrics'  => array(
			'variables' => array('deviceBandwidthMetrics' => NULL),
			'function' => 'theme_flowdeveloper_db_connected_devices_bandwidth_metrics',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes",
			'file' => 'flowdeveloper.theme.dashboard.inc',		
		),	
/*
		'flowdeveloper_user_profile_form'  => array(
			'variables' => array(),
			'template' => 'flowdeveloper.dashboard.user.profile.form',
			//'render element' => 'form',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes/templates",
			//'preprocess functions' => 'template_preprocess_flowdeveloper_user_profile_form',
		),
*/
		'flowdeveloper_dashboard_main'  => array(
			'template' => 'flowdeveloper.dashboard.main',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes/templates",
		),

		'flowdeveloper_logs_viewer'  => array(
			'variables' => array('logType' => NULL, 'logData' => NULL, 'pageCount' => NULL, 'currentPage' => NULL, 'logTypeForm' => NULL, 'pageSize' => NULL),
			'template' => 'flowdeveloper.dashboard.logs',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes/templates",
		),	

		'flowdeveloper_pager'  => array(
			'variables' => array('baseURL' => NULL, 'currentPage' => NULL, 'pageCount' => NULL),
			'function' => 'theme_flowdeveloper_pager',		
			'file' => 'flowdeveloper.theme.inc',
		),

		'flowdeveloper_temporary_metrics_placeholder' => array(
			'template' => 'flowdeveloper.temporary.metrics.placeholder',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes/templates",
		),
		/**
		'flowdeveloper_dashboard_content' => array(
			'variables' => array('headerLeft' => NULL, 'headerCenter' => NULL, 'headerRight' => NULL, 'mainContent' => NULL),
			'template' => 'flowdeveloper.dashboard.content',
			'path' => drupal_get_path('module', 'flowdeveloper') . "/themes/templates",
		),
		**/

	);

	$themes += _flowdeveloper_theme_devices();

	return $themes;
}

/**
 * Runs the custom hook hook_jstemplates defined by the flowdeveloper module 
 * 
 * Returns an array of javascript snippets that will be used by the ui. Any module can implement this hook
 * 
 * @param array $variables
 */
function flowdeveloper_preprocess_page(&$variables)
{
	$variables['jstemplates'] = implode(' ',module_invoke_all('jstemplates'));
}

/**
 * Themes inline text links on FDW
 * 
 * @param array $variables
 * @return string
 */
function theme_flowdeveloper_link(&$variables)
{
	if ($variables['isHtml']) 
	{
		$output = '<div class="c-flowdevel-link '. $variables['qualifier'].'">'
				. $variables['content']
				. '</div>';
	}
	else
	{
		$output = '<div class="c-flowdevel-link '. $variables['qualifier'].'">'
				. _flowdeveloper_l($variables['content'], $variables['path'])
				. '</div>';
	}
			
	return $output; 
}

/**
 * Theme the pager for any pages with listings
 * 
 * @param array $variables
 * @return string
 */
function theme_flowdeveloper_pager($variables)
{
	$baseURL = $variables['baseURL'];
	$currentPage = $variables['currentPage'];
	$pageCount = $variables['pageCount'];
	$output = '';
	$items = '';
	$next = '';
	$previous = '';
	
	if ( (count($pageCount) > 0) && isset($currentPage) && isset($baseURL)) 
	{
		for ($i = 1; $i <= $pageCount; $i++) 
		{
			$ateClass = 'c-ate-page-'.$i ;
			if ($i == $currentPage) 
			{
				$items .= '<li class="active c-ate-page-active '. $ateClass .'"><a href="'. $baseURL .'/'.$i.'">'. $i.'</a></li>'; 
			}
			else
			{
				$items .= '<li class="'. $ateClass .'"><a href="'. $baseURL .'/'.$i.'">'. $i.'</a></li>'; 
			}
		}
		
		if (($currentPage - 1) > 0) 
		{
			$pp = ($currentPage - 1);
			$previous = '<li class="previous c-ate-page-previous"><a href="'. $baseURL .'/'. $pp .'">Previous</a></li>';
		}
		
		if (($currentPage + 1) <= $pageCount) 
		{
			$np = ($currentPage + 1);
			$next = '<li class="next  c-ate-page-next"><a href="'. $baseURL .'/'. $np .'">Next</a></li>';
		}		
		
		$output = '<nav><ul class="pagination c-ate-pager">'
				. $previous
				. $items
				. $next
				. '</ul></nav>'	
				;
	}
	
	return $output;
}
