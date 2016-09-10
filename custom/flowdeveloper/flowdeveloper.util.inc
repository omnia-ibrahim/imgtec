<?php
/**
 * @file
 * This file contains general purpose functions used by the flowdeveloper module
 */



function _flowdeveloper_generic_error()
{
	return t('This is such an embarrasement! Something went wrong. Please try again.');
}

/**
 * A delegate for Drupal's l() function. Might change in the futures.
 *  
 * @param string $content
 * @param string $path
 * @param string $query
 * @param Array $htmlAttributes
 * @param Boolean $isHtmlContent
 * @param Boolean $isExternal
 */
function _flowdeveloper_l($content, $path, $query = null, $htmlAttributes = array(), $isHtmlContent = false, $isExternal = false)
{
	$options = array(
		'absolute' => true,
		'html' => $isHtmlContent,
		'external' => $isExternal,
		'query' => $query,
		'attributes' => $htmlAttributes,
	);
	
	return l($content, $path, $options);
}

/**
 * Validate if the string length is within the range of minimum and maximum characters.
 *
 * @param string $str
 * @param int $min
 * @param int $max
 * @return boolean whether the string length is within the range.
 */
function _flowdeveloper_validate_string_length($str, $min, $max){
	$len = strlen($str);
	if($len < $min){
		// string is shorter than minimum
		return false;
	}
	elseif($len > $max){
		// string is longer than maximum
		return false;
	}
	return true;
}

/**
 * Validate an email address. Checks that the e-mail has a valid syntax as well as a valid domain
 * Returns true if the email address has the email address format and the domain exists.
 * 
 * @param unknown_type $email
 * @return nothing the email is valid, error message when something is wrong.
 */
function _flowdeveloper_validate_email($email)
{
	if(!filter_var($email, FILTER_VALIDATE_EMAIL)) {
		return t('The email address is not valid.');
	};
}

/*
 * Valid username requirements;
 * UserName: Min length: 5 chars
 * UserName: Max length: 20 chars
 * UserName can include only the following: a-z, A-Z, 0123456789, dash, underscore & period
 *
 * Source: https://imgtec3.atlassian.net/wiki/display/FDW/FDW+User+Stories+-+Registration
 *
 * @param string $username
 * @return nothing the username is valid, error message when something is wrong.
 */
function _flowdeveloper_validate_username($username){
	if(preg_match('/^[a-z0-9]+[a-z0-9-_.]+$/i', $username)) {
		if(_flowdeveloper_validate_string_length($username,5,20)) {
			;
		}
		else
		{
			//username does not match the length requirement above
			return t('The username should be at least 5 characters long and no longer than 20 characters.');
		}
	}
	else
	{
		//username does not match the alphanumeric requirement above
		return t('The username is not valid.');
	}
}

/*
 * Valid password requirements;
 * Password: Min length: 6 chars
 * Password: Max length: 20 chars
 * Password: Must include a mix of upper & lower case
 * Password: Must include at least one number
 * Password confirmation: Must match Password
 *
 * Source: https://imgtec3.atlassian.net/wiki/display/FDW/FDW+User+Stories+-+Registration
 *
 * @param string $password
 * @return nothing the password is valid, error message when something is wrong.
 */
function _flowdeveloper_validate_password($password) {
	if(_flowdeveloper_validate_string_length($password, 6, 20)) {
		if(preg_match('/\d/', $password) && preg_match('/[a-z]/', $password) && preg_match('/[A-Z]/', $password)){
			;
		}
		else
		{
			// password doesn't contain at least one digit or lower or upper case characters
			return t('The password should contain at least one digit, one lower case and one upper case characters.');
		}
	}
	else
	{
		// pass doesn't match length requirements
		return t('The password should be at least 6 characters long and no longer than 20 characters.');
	}
}

/**
 * Returns true if the currently logged in user is a licensee admin
 * 
 * @return boolean
 */
function flowdeveloper_is_licensee_admin($email=null, $uid=null)
{
	global $user;
	$isAdmin = false;
	if ((!isset($email)) && (!isset($uid))) 
	{
		if ($user->uid) 
		{
			$oauthCredentials = flowautho_get_oauth_credentials($user->mail);
			if ($oauthCredentials['licensee_admin_id'] == $user->uid) 
			{
				$isAdmin = true;
			}
		}
	}
	else
	{
		$_user = user_load_by_mail($email);
		if ($_user) 
		{
                    $drupal_user_rid = variable_get('drupal_users_role_rid');
                    // Check if the current user is admin or in the Drupal users role to bypass authentication in flow
                    if (array_key_exists($drupal_user_rid, $_user->roles) || $_user->uid == 1) {
                       $isAdmin = true;
                    } else { 
	                $oauthCredentials = flowautho_get_oauth_credentials($email);
			if ($oauthCredentials['licensee_admin_id'] == $_user->uid) 
			{
				$isAdmin = true;
			}
                    }
		}		
	}
	
	return $isAdmin;	
}

/**
 * Convert a UTC date from the web service to an easily readable date
 * 
 * The time could potentially be added if required
 * 
 * @param string $utcTime
 */
function utcTimeToDate($utcTime = null)
{
	$date = null;
	if (isset($utcTime)) 
	{
		$dateParts = explode('T', $utcTime);
		$date = date('j, M Y', strtotime($dateParts[0]));;
	}
	return $date;
}

function flowdeveloper_utcTimeToDateTime($utcTime = null)
{
	$date = null;
	if (isset($utcTime)) 
	{
		$date = date('D d M Y H:i:s', strtotime($utcTime));
	}
	return $date;
}

/**
 * Convert digital storage from one unit to another. Note that not all possible conversions are handled
 * 
 * @param int $fromAmount
 * @param int $toAmount
 * @param string $from
 * @param string $to
 */
function flowdeveloper_convert_storage_units($fromAmount=null, $from=FDW_UNIT_KILOBYTE, $to=FDW_UNIT_MEGABYTE)
{
	$convertedAmount = null;
	if (isset($fromAmount) && ($fromAmount > 0)) 
	{
		/**
		 * Byte to Kilobyte OR Kilobytes to Megabytes
		 */
		if ( (($from == FDW_UNIT_KILOBYTE) && ($to == FDW_UNIT_BYTES)) || (($from == FDW_UNIT_MEGABYTE) && ($to == FDW_UNIT_KILOBYTE)) ) 
		{
			$convertedAmount = ($fromAmount * 1024);
		}
	}
	
	return $convertedAmount;
}