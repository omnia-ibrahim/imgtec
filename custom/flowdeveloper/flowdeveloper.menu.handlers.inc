<?php
/**
 * @file
 * This file contains the function definitions for all callback functions used in hook_menu
 */

/**
 * Load the homepage
 */
function flowdeveloper_generate_homepage()
{
	return theme('flowdeveloper_homepage');
}

/**
 * Generate the registration page
 */
function flowdeveloper_generate_registration_page()
{
	return theme('flowdeveloper_user_registration');
}

/**
 * Generate a list of current Creator licensees 
 */
function flowdeveloper_generate_licensee_list()
{
	return theme('flowdeveloper_licensee_list', array('licensees' => flowdeveloper_get_licensee_list()));
}

/**
 * Return true if the user's email address could be validated by FlowCloud using the supplied token
 * 
 * This menu handler will be used when the verification link is of the following format:
 * http://flow.imgtec.com/developers/validate/{$token}/
 * 
 * @param string $token
 * @return boolean
 */
function flowdeveloper_validate_email($token,  $locale = null)
{
	if (isset($token) && ( strlen($token) > 0)) 
	{
		if (flowdeveloper_activate_user_account($token)) 
		{
			drupal_get_messages(NULL, true);
			$msg = 'You have successfully validated your FlowCloud developer account. You can now sign-in.';
			flowautho_set_message('c-ate-account-activation-success', $msg, 'status', true);
			drupal_goto("user/login");			
		}
		else
		{
			drupal_get_messages(NULL, true);
			$msg = 'Your account activation failed. Are you sure you have the right activation code? Also check if your activation code has expired.';
			flowautho_set_message('c-ate-account-activation-error', $msg, 'error', true);
			drupal_goto("<front>");				
		}
	}
	else
	{
		$msg = 'Your account activation failed. The activation code needs to be provided.';
		flowautho_set_message('c-ate-account-activation-error', $msg, 'error');	
	}
	
	//drupal_goto("user/login");
}

/**
 * Returns true if the user's email address could be validated by FlowCloud using the supplied token and licensee identifier
 * 
 * This menu handler will be used when the verification link is of the following format:
 * http://flow.imgtec.com/developers/(validate|confirm)/{$licenseeid}/{$token}/{$locale}
 *  
 * @param int $licenseeid
 * @param string $token
 * @param string $locale
 * @return boolean
 */
function flowdeveloper_confirm_email($licenseeid, $token, $locale = null)
{
	if (isset($licenseeid) && isset($token) && ( strlen($token) > 0)) 
	{
		if (flowdeveloper_activate_user_account($token, $licenseeid)) 
		{
			drupal_get_messages(NULL, true);
		$msg = 'You have successfully validated your Creator account. You can now sign-in.';
			flowautho_set_message('c-ate-account-activation-success', $msg, 'status', true);
			drupal_goto("user/login");			
		}
		else
		{
			drupal_get_messages(NULL, true);
			$msg = 'Your account activation failed. Are you sure you have the right activation code? Also check if your activation code has expired.';
			flowautho_set_message('c-ate-account-activation-error', $msg, 'error', true);
			drupal_goto("<front>");				
		}

	}
	else
	{
		drupal_get_messages(NULL, true);
		$msg = 'Your account activation failed. Are you sure you have the right activation code?';
		flowautho_set_message('c-ate-account-activation-error', $msg, 'error', true);
		drupal_goto("<front>");			
	}
	
}
