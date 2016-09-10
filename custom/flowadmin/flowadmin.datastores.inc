<?php

define('FLOWADMIN_DATASTORES', 'datastores');

/**
 * Return a list of device types related menu paths
 * Enter description here ...
 */
function _flowadmin_menu_datastores()
{
	$items = array();
	
	$items[FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DATASTORES.'/%'] = array(
		'title' => t('Datastores'),
		'description' => t('Datastores list'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowadmin_generate_datastores_page',
		'page arguments' => array(3),
		'type' => MENU_NORMAL_ITEM,
		'weight' => 52,
	);
	
	
	$items[FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DATASTORES.'/'.FLOWADMIN_ADD] = array(
		'title' => t('Add a Datastore'),
		'description' => t('Add a DataStore to a particular tenant'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowadmin_generate_add_datastore_page',
		'page arguments' => array(NULL),
		'type' => MENU_NORMAL_ITEM,
		'weight' => 52,
	);
	

	
	$items[FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DATASTORES.'/'.FLOWADMIN_UPGRADE] = array(
		'title' => t('Datastores Upgrade Message'),
		'description' => t('Call to action to upgrade inorder to be able to create more Datastores'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowadmin_generate_datastores_limits_page',
		'type' => MENU_NORMAL_ITEM,
		'weight' => 52,
	);
	
	$items[FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DATASTORES.'/%/'.FLOWADMIN_DELETE] = array(
		'title' => t('Delete datastore'),
		'description' => t('Delete a datastore'),
		'access callback' => 'user_is_logged_in',
		'page callback' => 'flowadmin_delete_datastore',
		'page arguments' => array(3),	
		'type' => MENU_NORMAL_ITEM,
		'weight' => 50,
	);		
	
	return $items;
}


function _flowadmin_theme_datastores()
{
	$items = array(
	
		'flowadmin_datastores_headerright'  => array(
			'variables' => array('url' => NULL),
			'template' => 'flowadmin.datastores.headerright',
			'path' => drupal_get_path('module', 'flowadmin') . "/themes",
		),	

		'flowadmin_datastores_maincontent'  => array(
			'variables' => array('datastores' => NULL, 'pageCount' => NULL, 'pageNumber' => NULL),
			'template' => 'flowadmin.datastores.maincontent',
			'path' => drupal_get_path('module', 'flowadmin') . "/themes",
		),

		'flowadmin_datastores_btn_panel'  => array(
			'variables' => array('datastore' => NULL),
			'template' => 'flowadmin.datastores.btn_panel',
			'path' => drupal_get_path('module', 'flowadmin') . "/themes",
		),	
	
	);
	
	return $items;
}

function flowadmin_generate_datastores_page()
{
	global $user;
	$htmlOutput = null;
	
	flowadmin_access();
	
	try {
			$pageNumber = func_get_arg(0);
			$pageNumber = (isset($pageNumber)) ? $pageNumber : 1;
			$pageSize = 10;
			$oauthInfo = flowautho_get_oauth_credentials($user->mail);
			$datastoreServices = new FDWDatastoreServicesImpl($oauthInfo, $user);
			$datastoresContainer = $datastoreServices->getDatastores($pageNumber, $pageSize);
			$datastores = $datastoresContainer['items'];
			
			//drupal_set_message('<pre>[flowadmin_generate_datastores_page:: ] Topics:: '. print_r($datastoresContainer, true).'</pre>');
			if ($datastoresContainer['canCreate']) 
			{
				$addURL = base_path() . FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DATASTORES.'/'.FLOWADMIN_ADD;
			}
			else
			{
				$addURL = base_path() . FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DATASTORES.'/'.FLOWADMIN_UPGRADE;
			}
			
			$headerLeft = '';
			$headerRight = theme('flowadmin_datastores_headerright', array('url' => $addURL));
			$contentArgs =  array('datastores' => $datastores, 'pageCount' => $datastoresContainer['pagecount'], 'pageNumber' => $pageNumber);
			$mainContent = theme('flowadmin_datastores_maincontent', $contentArgs);
				
			$htmlOutput =  theme('flowautho_dashboard_content', array('headerLeft' => $headerLeft, 
													  'headerCenter' => t('Datastores'),  
													  'headerRight' => $headerRight, 
													  'mainContent' => $mainContent));	
					
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDatastoreServicesImpl error:: '. print_r($e->getMessage(),true));
	}
	
	return $htmlOutput;	
}

function flowadmin_generate_add_datastore_page()
{
	global $user;
	$htmlOutput = null;
	
	flowadmin_access();
		
	$datastoreForm = drupal_get_form('flowadmin_datastore_form');
	
	$headerLeft = '';
	$headerRight = '';
	$mainContent = drupal_render($datastoreForm);
	$pageTitle = t('Create a datastore') ;
		
	$htmlOutput =  theme('flowautho_dashboard_content', array('headerLeft' => $headerLeft, 
											  'headerCenter' => $pageTitle,  
											  'headerRight' => $headerRight, 
											  'mainContent' => $mainContent));

	return $htmlOutput;
}

function flowadmin_datastore_form($form, &$form_state)
{
	$form = array();
	
	$form['name'] = array(
	  '#type' => 'textfield', 
	  '#title' => 'Name',
	  '#description' => t('Only a-z, A-Z, 0123456789, "_" and "-" are allowed and no more than 50 characters.'),	
	  '#maxlength' => 50,
	  '#required' => TRUE,
	  '#attributes' => array('class' => array('c-ate-datastore-form-name')),
	  '#default_value' => '', 
	 
	);	
	
	$form['isdeviceds'] = array(
	   '#type' => 'checkbox', 
	   '#title' => 'Is a Device datastore',
	   '#description' => t('User owned devices will be able to use this datastore'),	
	   '#attributes' => array('class' => array('c-ate-datastore-form-isdeviceds')),
	   '#default_value' => true,  
	);	
	
	$form['isuserds'] = array(
	   '#type' => 'checkbox', 
	   '#title' => 'Is a User datastore',
	   '#description' => t('Users will be able to subscribe to this topic'),	
	   '#attributes' => array('class' => array('c-ate-datastore-form-isuserds')),
	   '#default_value' => true,  
	);

		
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
		'#attributes' => array('class' => array('c-ate-datastore-form-submit-btn')),
	);	

	$prefixe = '<div class="row c-ate-datastore-form c-ate-datastore-form-wrapper">'
			 . '	<div class="col-xs-12 col-sm-5 col-lg-4">';
	$suffix  = '	</div>'
			 . '</div>';
		
	$form['#prefix'] = $prefixe;
	$form['#suffix'] = $suffix;		
	
	return $form;
}

function flowadmin_datastore_form_validate($form, &$form_state)
{
	$isDD = ($form_state['values']['isdeviceds'] != 0) ? true : false;
	$isUD = ($form_state['values']['isuserds'] != 0) ? true : false;
	
	$validateResponse = _flowadmin_validate_topic_name($form_state['values']['name']);
	if (!$validateResponse['isvalid']) 
	{
		form_set_error('name', '<div class="c-ate-datastore-form-name-error">'.$validateResponse['error']['msg'].'</div>');
	}
	
	if ((!$isDD) && (!$isUD)) 
	{
		$ateClasses = 'c-ate-datastore-isdeviceds-error c-ate-datastore-isuserds-error ';
		$msg = t('Please indicate if this datastore is a User or Device datastore, or both.');
		form_set_error('isdeviceds', '<div class="'. $ateClasses.'">'. $msg .'</div>');
		form_set_error('isuserds', null);
	}	
}

function flowadmin_datastore_form_submit($form, &$form_state)
{
	global $user;
	
	$name = $form_state['values']['name'];
	$isDD = ($form_state['values']['isdeviceds'] != 0) ? true : false;
	$isUD = ($form_state['values']['isuserds'] != 0) ? true : false;
	
	try {
		
		$oauthInfo = flowautho_get_oauth_credentials($user->mail);
		$datastoreServices = new FDWDatastoreServicesImpl($oauthInfo, $user);
		
		if ($datastoreServices->createDatastore($name, $isDD, $isUD)) 
		{
			$msg = t('Your new datastore was successfully created.');
			flowautho_set_message('c-ate-datastore-form-createdatastore-success', $msg, 'status', true);
			drupal_goto(FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DATASTORES.'/1');				
		}
		else
		{
			$msg = t('Sorry an error occured while trying to create your new datastore.');
			flowautho_set_message('c-ate-datastore-form-createdatastore-error', $msg, 'error', false);			
		}
		
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDatastoreServicesImpl error:: '. print_r($e->getMessage(),true));
	}	
		
}

function flowadmin_generate_datastores_limits_page()
{
	global $user;
	$htmlOutput = null;
	
	flowadmin_access();
		
	$content = '<p>'. t('You have exhausted your Datastores allowance. Please upgrade your plan in order to be able to create more Datastores').'</p>';	
	$headerLeft = '';
	$headerRight = '';
	$pageTitle = t('Upgrade Your Subscription') ;
	$htmlOutput =  theme('flowautho_dashboard_content', array('headerLeft' => '', 'headerCenter' => $pageTitle, 'headerRight'=>'', 'mainContent'=>$content));
		
	return $htmlOutput;			
}

function flowadmin_delete_datastore()
{
	global $user;
	$datastoreName = func_get_arg(0);
	
	flowadmin_access();	
	
	if (isset($datastoreName)) 
	{
		try {
			
			$oauthInfo = flowautho_get_oauth_credentials($user->mail);
			$datastoreServices = new FDWDatastoreServicesImpl($oauthInfo, $user);
			
			if ($datastoreServices->deleteDatastore($datastoreName)) 
			{
				$msg = t('The datastore was successfully deleted.');
				flowautho_set_message('c-ate-datastore-form-deletedatastore-success', $msg, 'status', true);
				drupal_goto(FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DATASTORES.'/1');			
			}
			else
			{
				$msg = t('Sorry an error occured while trying to delete the datastore.');
				flowautho_set_message('c-ate-datastore-form-deletedatastore-error', $msg, 'error', false);	
			}
			
		} catch (FDWUnknownUserException $e) {
			watchdog('error', 'FDWDatastoreServicesImpl error:: '. print_r($e->getMessage(),true));
		}				
	}
	else
	{
		$msg = t('Sorry we could not find the datastore you are trying to delete.');
		flowautho_set_message('c-ate-datastore-form-deletedatastore--nodatastore-error', $msg, 'error', false);			
	}	
}