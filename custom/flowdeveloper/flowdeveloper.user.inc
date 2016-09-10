<?php

define('FDW_LOGINREDIRECT', 'LoginRedirect');

/**
 * Alter the user registration form provided by the user module (core)
 * 
 * @param Array $form
 * @param Array $form_state
 */
function flowdeveloper_form_user_register_form_alter(&$form, &$form_state, $form_id)
{
  global $user;
  $drupal_user_rid = variable_get('drupal_users_role_rid');
  // Check if the current user is admin or in the Drupal users role to bypass authentication in flow
  if (array_key_exists($drupal_user_rid, $user->roles) || $user->uid == 1) {
    return;    
  } else {
	$form['account']['name']['#title_display'] = 'invisible';
	$form['account']['name']['#attributes']['placeholder'] = t("Username");
	$form['account']['name']['#attributes']['class'][] = "c-ate-registration-username";
	$form['account']['name']['#field_suffix'] = '<div class="form-control-feedback c-reg-user-icon"></div>';
	unset($form['account']['name']['#description']);

	$form['account']['mail']['#title_display'] = 'invisible';
	$form['account']['mail']['#attributes']['placeholder'] = t("Email");
	$form['account']['mail']['#attributes']['class'][] = "c-ate-registration-email";
	$form['account']['mail']['#field_suffix'] = '<div class="form-control-feedback c-reg-mail-icon"></div>';
	unset($form['account']['mail']['#description']);

	$form['account']['pass']['#type'] = 'password';
	$form['account']['pass']['#title'] = t('Password');
	$form['account']['pass']['#title_display'] = 'invisible';
	$form['account']['pass']['#attributes']['placeholder'] = t("Password");
	$form['account']['pass']['#attributes']['class'][] = "c-ate-registration-password";
	$form['account']['pass']['#field_suffix'] = '<div class="form-control-feedback c-reg-pass-icon"></div>';
	unset($form['account']['pass']['#description']);

	$form['account']['pass2']['#type'] = 'password';
	$form['account']['pass2']['#title'] = 'Confirm Password';
	$form['account']['pass2']['#title_display'] = 'invisible';
	$form['account']['pass2']['#attributes']['placeholder'] = "Confirm Password";
	$form['account']['pass2']['#attributes']['class'][] = "c-reg-pass2";

	$form['actions']['submit']['#attributes']['class'][] = "c-reg-submit";
	$form['actions']['submit']['#attributes']['class'][] = "c-ate-registration-create";
	$form['actions']['submit']['#attributes']['class'][] = "btn-primary";
	/**
	 * replace Drupal's registration validation with FDW's.
	 */
	$form['#validate'][0] = 'flowdeveloper_user_register_form_validate';

	/**
	 * Drupal will be called upon to complete user registration in FDW's submit function
	 */
	$form['#submit'] = array('flowdeveloper_user_register_form_submit');
	
			
	$form['#after_build'][] = '_flowdeveloper_form_user_register_form_after_build';
  }
}

/**
 * Validate user registration form
 * @param array $form
 * @param array $form_state
 */
function flowdeveloper_user_register_form_validate($form, &$form_state)
{
	$account = $form['#user'];
	// Validate new or changing username.
	if (isset($form_state['values']['name'])) {
		if ($error = _flowdeveloper_validate_username($form_state['values']['name'])) {
			form_set_error('name', '<div class="c-ate-registration-error-invalid-username">'.$error.'</div>');
		}
		elseif ((bool) db_select('users')->fields('users', array('uid'))->condition('uid', $account->uid, '<>')->condition('name', db_like($form_state['values']['name']), 'LIKE')->range(0, 1)->execute()->fetchField()) {
			form_set_error('name', '<div class="c-ate-registration-error-exist-username">'.t('The name %name is already taken.', array('%name' => $form_state['values']['name'])).'</div>');
		}
	}

	// Trim whitespace from mail, to prevent confusing 'e-mail not valid'
	// warnings often caused by cutting and pasting.
	$mail = trim($form_state['values']['mail']);
	form_set_value($form['account']['mail'], $mail, $form_state);

	// Validate the e-mail address, and check if it is taken by an existing user.
	if ($error = _flowdeveloper_validate_email($form_state['values']['mail'])) {
		form_set_error('mail', '<div class="c-ate-registration-error-invalid-email">'.$error.'</div>');
	}
	elseif ((bool) db_select('users')->fields('users', array('uid'))->condition('uid', $account->uid, '<>')->condition('mail', db_like($form_state['values']['mail']), 'LIKE')->range(0, 1)->execute()->fetchField()) {
		form_set_error('mail', '<div class="c-ate-registration-error-exist-email">'
							 .t('The e-mail address %email is already registered. <a href="@password">Have you forgotten your password?</a>', array('%email' => $form_state['values']['mail'], '@password' => url('user/password')))
							 .'</div>'
		);
	}

	// Validate the password.
	if ($error = _flowdeveloper_validate_password($form_state['values']['pass'])) {
		form_set_error('pass', '<div class="c-ate-registration-error-invalid-pass">'.$error.'</div>');
	}

	//Validate honey pot
	if (isset($form_state['values']['pass2']) && $form_state['values']['pass2'] != '') {
		form_set_error('','<div class="c-ate-registration-error-generic">'.t("Failed to register user account.").'</div>');
	}
}

/**
 * Register user with FlowCloud and Drupal
 * 
 * @param array $form
 * @param array $form_state
 */
function flowdeveloper_user_register_form_submit($form, &$form_state)
{
	global $language;

	$admin = $form_state['values']['administer_users'];

	// Remove unneeded values.
	form_state_values_clean($form_state);

	$form_state['values']['pass'] = $form_state['values']['pass'];
	$form_state['values']['init'] = $form_state['values']['mail'];

	$account = $form['#user'];
	$account->is_new = true;

	try {
		$userInfo = array();
		//$userInfo['username'] = $form_state['values']['mail'];
		$userInfo['username'] = $form_state['values']['name'];
		$userInfo['email'] = $form_state['values']['mail'];
		$userInfo['password'] = $form_state['values']['pass'];
		$userInfo['locale'] = $language->language;
		$userInfo['allow_dm'] = '0';
		$userInfo['allow_email_comms'] = '0';

		$oauthInfo = flowautho_get_oauth_credentials_by_licensee_id(FLOWAUTH_DEFAULT_LICENSEE_ID);

		$fdwUserServices = new FDWUserServicesImpl($oauthInfo);
		$flowGUID = $fdwUserServices->createUser($userInfo, TRUE);
		
		if ($flowGUID == FDWUserServicesImpl::USER_EXISTS) 
		{
			drupal_set_message('<div class="c-ate-registration-error-user-exists">'.t("Sorry your chosen e-mail address is already being used.").'</div>', 'error');
			$form_state['redirect'] = 'user/login';
			return;				
		}
		elseif (!isset($flowGUID))
		{
			drupal_set_message('<div class="c-ate-registration-error-generic">'.t("Failed to register user account.").'</div>', 'error');
			$form_state['redirect'] = '';
			return;			
		}

		/**
		if(!isset($flowGUID)) 
		{
			drupal_set_message('<div class="c-ate-registration-error-generic">'.t("Failed to register user account.").'</div>', 'error');
			$form_state['redirect'] = '';
			return;
		}
		**/
		
		
	} catch (FDWBadRequestException $e) {
		drupal_set_message('<div class="c-ate-registration-error-generic">'.t("Failed to register user account.").'</div>', 'error');
		$form_state['redirect'] = '';
		return;
	}

	$edit['name'] = $form_state['values']['name'];
	$edit['mail'] = $form_state['values']['mail'];
	$edit['pass'] = $form_state['values']['pass'];
	$edit['init'] = $form_state['values']['mail'];
	$edit['status'] = 1;
	$edit['language'] = $language->language;
	$data['licensee_id'] = $oauthInfo['licensee_id'];
	$data['lounge2_guid'] = $flowGUID;
	$edit['data'] = $data;

	$account = user_save($account, $edit);

	// Terminate if an error occurred during user_save().
	if (!$account) {
		drupal_set_message('<div class="c-ate-registration-error-generic">'.t("Failed to register user account.").'</div>', 'error');
		$form_state['redirect'] = '';
		return;
	}
	$form_state['user'] = $account;
	$form_state['values']['uid'] = $account->uid;

	watchdog('user', 'New user: %name (%email).', array('%name' => $form_state['values']['name'], '%email' => $form_state['values']['mail']), WATCHDOG_NOTICE, l(t('edit'), 'user/' . $account->uid . '/edit'));

	// New administrative account without notification.
	if ($admin) {
		$uri = entity_uri('user', $account);
		drupal_set_message(t('Created a new user account for <a href="@url">%name</a>. No e-mail has been sent.', array('@url' => url($uri['path'], $uri['options']), '%name' => $account->name)));
	}
	// Normal user account created.
	elseif (!$admin) {
		//$form_state['uid'] = $account->uid;
		//user_login_submit(array(), $form_state);
		drupal_set_message('<div class="c-ate-registration-success">'.t('Registration successful. Please check your email inbox for activation email').'</div>');
		$form_state['redirect'] = 'user/login';
	}
}

/**
* Alter the user login form provided by the user module (core)
* 
* @param array $form
* @param array $form_state
* @param array $form_id
*/
function flowdeveloper_form_user_login_alter(&$form, &$form_state, $form_id)
{

	$form['name']['#title_display'] = 'invisible';
	$form['name']['#attributes']['placeholder'] = t("Email");
	$form['name']['#attributes']['class'][] = "c-ate-login-email";
	$form['name']['#field_suffix'] = '<div class="form-control-feedback c-reg-mail-icon"></div>';
	unset($form['name']['#description']);
	
	$form['pass']['#type'] = 'password';
	$form['pass']['#title'] = t('Password');
	$form['pass']['#title_display'] = 'invisible';
	$form['pass']['#attributes']['placeholder'] = t("Password");
	$form['pass']['#attributes']['class'][] = "c-ate-login-password";
	$form['pass']['#field_suffix'] = '<div class="form-control-feedback c-reg-pass-icon"></div>';
	unset($form['pass']['#description']);

	//$form['#validate'][0] = 'flowdeveloper_form_user_login_validate';
	/**
	 * The validation functions have been re-set omitting one of the original validation function i.e. "user_login_authenticate_validate"
	 * This function has been omitted because it tries to load the user account using their username field though we have passed in 
	 * the user's email address as their username. So this naturally fails. 
	 * 
	 * It also authenticates the user using the username and supplied password which is bound to fail for our users 
	 * as their passwords have been re-written during the migration from Drupal 6 to 7. Drupal 6 password was stored as an md5 string
	 * but Drupal 7 hashes the password. We do not mind this change because all our users are authenticated against FlowCloud and not
	 * against the local database. 
	 * 
	 */
	 //$form['#validate'] = array('flowdeveloper_form_user_login_validate', 'flowautho_login_user', 'user_login_final_validate');
	$form['#validate'] = array('flowdeveloper_form_user_login_validate', 'flowautho_login_user', 'user_login_final_validate');
	$form['#submit'][] = 'flowdeveloper_form_user_login_submit';
	$form['actions']['submit']['#attributes']['class'][] = "c-login-submit";
	$form['actions']['submit']['#attributes']['class'][] = "c-ate-login-submit-button";
	$form['actions']['submit']['#attributes']['class'][] = "btn-primary";
	//_flowautho_debug('[flowdeveloper_form_user_login_form_alter::] ' . print_r($form, true));
	
//	$form['#after_build'][] = '_flowdeveloper_form_user_login_form_after_build';
	
}


function flowdeveloper_form_user_login_validate($form, &$form_state)
{
	$drupalErrors = drupal_get_messages('error', true);
	//$formErrors = form_get_errors();
	$form_state['values']['name'] = trim($form_state['values']['name']);
	if ( ((!isset($form_state['values']['name'])) || (!filter_var($form_state['values']['name'], FILTER_VALIDATE_EMAIL))) && !flowautho_is_admin_account($form_state['values']['name']) ) 
	{
		flowautho_set_message('c-ate-login-error-invalid-email', t('Please enter a valid e-mail address'), 'error');
	}
	
	if (!isset($form_state['values']['pass'])) 
	{
		flowautho_set_message('c-ate-login-error-invalid-password', t('Please enter a password'), 'error');             
	}
        if (flowautho_is_admin_account($form_state['values']['name']) && valid_email_address($form_state['values']['name'])) {   
        
          if ($name = db_query("SELECT name FROM {users} WHERE LOWER(mail) = LOWER(:name)", array(
      ':name' => $form_state['values']['name'],
    ))->fetchField()) {
         form_set_value($form['name'], $name, $form_state);
         }
        }
	           
	//_flowautho_debug('[flowdeveloper_form_user_login_validate::] FormSta');           
}

function flowdeveloper_form_user_login_submit($form, &$form_state)
{
	global $user;
	//_flowautho_debug('[flowdeveloper_form_user_login_submit::] ');
	if ($user->uid) 
	{
		if(isset($_COOKIE[FDW_LOGINREDIRECT]) && $_COOKIE[FDW_LOGINREDIRECT]) {
			$form_state['redirect'] = $_COOKIE[FDW_LOGINREDIRECT];
			unset($_COOKIE[FDW_LOGINREDIRECT]);
			setcookie(FDW_LOGINREDIRECT, null, -1, '/');
		} else {
			$form_state['redirect'] = FDW_DASHBOARD;
		}
	}
}


/**
 * Utility function to actually activate a user's account
 * 
 * @param string $token
 * @param int $licenseeid
 */
function flowdeveloper_activate_user_account($token, $licenseeid=FLOWAUTH_DEFAULT_LICENSEE_ID)
{
	$licensee = flowautho_get_oauth_credentials_by_licensee_id($licenseeid);
	$accountActivated = false;
	if (is_array($licensee) && isset($licensee['licensee_id'])) 
	{
		$userServices = new FDWUserServicesImpl($licensee);
		if ($userServices->activateUser($token)) 
		{
			$msg = 'You have successfully validated your Creator account. You can now sign-in.';
			flowautho_set_message('c-ate-account-activation-success', $msg);
			$accountActivated = true;
		}
		else
		{
			$msg = 'Your account activation failed. Are you sure you have the right activation code?';
			flowautho_set_message('c-ate-account-activation-error', $msg, 'error');	
		}
	}
	else
	{
		$msg = 'Your account activation failed. A valid Creator key could not be found.';
		flowautho_set_message('c-ate-account-activation-error', $msg, 'error');	
	}
	
	return $accountActivated;
}

/**
 * Returns the fcap code for user device registration
 */
function flowdeveloper_get_fcap(){

	//Get user
	global $user;

	//Get OAuth keys for user
	$oauthInfo = flowautho_get_oauth_credentials($user->mail);
	$code = 'Sorry an error occured while trying to retrieve your code. Please try again later.';

	try {
			//Create a device management services object and retrieve the code
			$deviceManServices = new FDWDeviceManagementServicesImpl($oauthInfo, $user);
			$FCAPCode = $deviceManServices->getFCAPCode();
			$code = $FCAPCode['fcapcode']; 
		
	} catch (FDWUnknownUserException $e) {
		watchdog('error', 'FDWDeviceManagementServicesImpl error:: '. $e->getMessage(),true);
	}
	
	echo $code;	

}

/**
 * Resets the user's password using the token
 * 
 * @param string $token
 */
function flowdeveloper_password_reset($token)
{
	$uriParts = explode('/', $_GET['q']);
	$partCount = count($uriParts);
	if ($partCount == 3) 
	{
		/**
		 * This variable might be preconfigured in the sites settings.php
		 */
		$licenseeID = FLOWAUTH_DEFAULT_LICENSEE_ID; 
		$token = $uriParts[($partCount - 1)];
	}
	elseif ($partCount == 4)
	{
		$licenseeID = $uriParts[($partCount - 2)];
		$token = $uriParts[($partCount - 1)];		
	}

	$oauthInfo = flowautho_get_oauth_credentials_by_licensee_id($licenseeID);
	
	$fdwUserServices = new FDWUserServicesImpl($oauthInfo);
	if ($fdwUserServices->resetPassword($token)) 
	{
		$msg = 'Your password has been reset.';
		$output = t('Details of your new password have been sent to your e-mail address.');	 
		flowautho_set_message('c-ate-password-reset-success', t($msg));			
	}
	else
	{
		$msg = 'Resetting your password has been unsuccessful. Please try again or contact support. ';
		$output = t('Are you sure you followed the right link? ');
		flowautho_set_message('c-ate-password-reset-error', t($msg) , 'error');			
	}
	
	return $output;
}

function flowdeveloper_form_user_pass_alter(&$form, &$form_state)
{
	//drupal_set_message('<pre>'. print_r($form, true).'</pre>');
	
	$introText  = '<h3>Trouble logging in?</h3>'
				. '<p>' . t('Enter your email address below to request a new password  or activation email.') . '</p>';
				
	$form['desired_op'] = array('#type' => 'hidden', '#default' => 'none');
	
	$form['intro'] = array('#value' => $introText);
	
	$form['name']['#title_display'] = 'invisible';
	$form['name']['#required'] = false;
	$form['name']['#attributes']['placeholder'] = t("E-mail address");
	$form['name']['#attributes']['class'][] = "c-ate-resend-password-email";
	$form['name']['#field_suffix'] = '<div class="form-control-feedback c-reg-mail-icon"></div>';
	unset($form['name']['#description']);	
		
	
	//$form['#submit'] = is_array($form['#submit']) ? $form['#submit'] : array();
	
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#name' => 'op-send-new-pword',
		'#value' => t('Send new password'),
		'#button_type' => 'inline-button',
	);
	
	$form['actions']['submit']['#attributes']['class'][] = "c-resend-passord-btn";
	$form['actions']['submit']['#attributes']['class'][] = "c-ate-resend-password-submit-button";
	$form['actions']['submit']['#attributes']['class'][] = "btn-primary";	
	
	$form['actions']['submit_activation'] = array(
		'#type' => 'submit',
		'#name' => 'op-resend-activation-link',
		'#value' => t('Send new account activation email'),
		'#button_type' => 'inline-button',
	);
	
	$form['actions']['submit_activation']['#attributes']['class'][] = "c-resend-act-email-btn";
	$form['actions']['submit_activation']['#attributes']['class'][] = "c-ate-resend-activation-email-submit-button";
	$form['actions']['submit_activation']['#attributes']['class'][] = "btn-primary-inverse";


	
	//$form['#theme'] = 'flowdeveloper_form_password_problems';
	
	$form['#validate'] = is_array($form['#validate']) ? $form['#validate'] : array();
	
	$key = array_search('user_pass_validate', $form['#validate']);
	if ($key !== FALSE)
	{
		$form['#validate'][$key] = 'flowdeveloper_form_user_pass_validate';
	}
	
	$form['#submit'] = is_array($form['#submit']) ? $form['#submit'] : array();
	$key = array_search('user_pass_submit', $form['#submit']);
	if ($key !== FALSE)
	{
		$form['#submit'][$key] = 'flowdeveloper_form_user_pass_submit';
	}
	
}

function flowdeveloper_form_user_pass_validate($form, &$form_state)
{
	$email = $form_state['values']['name'];
	
	if (isset($email) && filter_var($email, FILTER_VALIDATE_EMAIL)) 
	{
		if($form_state['values']['desired_op'] == 'send-new-password')
		{
			$userInfo = flowautho_drupal_knows_user($form_state['values']['name']);
			if ( isset($userInfo['uid']) && ( !flowautho_flow_knows_user($form_state['values']['name']) ) ) 
			{
				if (flowdeveloper_send_missing_licensee_info_email($form_state['values']['name'])) 
				{
					watchdog('flowdeveloper', 'User account is missing the LicenseeID. User email: '.$form_state['values']['name']);
					$msg = 'We have identified a problem with your account. Our support staff has been informed and they will be in touch with you shortly to address the issue.';
					$_SESSION[FLOWDEVEL_SKEY_SHOWMSG] = $msg;
					drupal_goto('/');
				}
			}
			
			
			if (isset($userInfo['uid'])) 
			{
				
				try {
					
					$oauthInfo = flowautho_get_oauth_credentials_by_licensee_id(FLOWAUTH_DEFAULT_LICENSEE_ID);
					$fdwUserServices = new FDWUserServicesImpl($oauthInfo);
					//$resCode = $fdwUserServices->requestNewPassword($form_state['values']['name']);
					$resCode = $fdwUserServices->requestNewPassword($userInfo['data']['lounge2_guid']);
					
					//_flowautho_debug('[flowdeveloper_form_user_pass_validate::] ResponseCode:: '. $resCode);
					//_flowautho_debug('[flowdeveloper_form_user_pass_validate::] ResponseCode:: '. print_r($userInfo, true));
						
					switch ($resCode)
					{
						case '201':
							$msg = t('Instructions on how to reset your password have been sent to your e-mail address.');
							$ateClasses = 'c-ate-resend-password-success';
							flowautho_set_message($ateClasses, $msg, 'status', true);
							break;
						case '400':
							// anti-spam:
							flowautho_set_form_error('mail', 'c-ate-resend-password-error-antispam', t( 'You\'ve already requested an email from us recently. To prevent email spam, you cannot request multiple times within a 10 minute window. Please check your inbox or wait 10 minutes and try again.' ));
							break;
						case '401':
							flowautho_set_form_error('mail', 'c-ate-resend-password-error-unactivated-account', t( 'Sorry, you cannot reset your password at this time as your account has not been activated. To activate your account, please click on the link in your account activation e-mail, or request a new account activation e-mail by clicking on the "Resend account activation e-mail" button.' ));
							return;
						case '404':
							// TODO: get proper error codes from web service doc
							flowautho_set_form_error('mail', 'c-ate-resend-password-error-unrecognized-email', t('Unrecognised e-mail address'));
							break;
						default:
							watchdog('flowdeveloper','reset password unknown status '.$resCode);
							drupal_set_message('<div class="c-ate-resend-password-error-generic">'.t("Failed to resend your password.").'</div>', 'error');
							break;
					}
					
				} catch (Exception $e) {
					
					drupal_set_message('<div class="c-ate-resend-password-error-generic">'.t("Failed to resend your password.").'</div>', 'error');
					$form_state['redirect'] = '';
					return;
				}
			}
			else 
			{
				flowautho_set_form_error('name', 'c-ate-resend-password-error-unrecognized-email', t('Unrecognised e-mail address'));
			}
			
		}
		elseif ($form_state['values']['desired_op'] == 'send-acc-activation-email')
		{
			
			$userInfo = flowautho_drupal_knows_user($form_state['values']['name']);
			if (isset($userInfo['uid'])) 
			{
				try {
					
						$oauthInfo = flowautho_get_oauth_credentials_by_licensee_id(FLOWAUTH_DEFAULT_LICENSEE_ID);
						$fdwUserServices = new FDWUserServicesImpl($oauthInfo);
						//$resCode = $fdwUserServices->requestAccountActivationEmail($form_state['values']['name']);
						$resCode = $fdwUserServices->requestAccountActivationEmail($userInfo['data']['lounge2_guid']);
						
						//_flowautho_debug('[flowdeveloper_form_user_pass_validate::] ResponseCode:: '. $resCode);
						//_flowautho_debug('[flowdeveloper_form_user_pass_validate::] ResponseCode:: '. print_r($userInfo, true));
						
						switch ($resCode)
						{
							case '201':
								$msg = t('Activation instructions have been sent to your e-mail address.');
								$ateClasses = 'c-ate-resend-account-activation-email-success';
								flowautho_set_message($ateClasses, $msg, 'status', true);
								break;
							case '400':
								// anti-spam:
								$msg = t( 'You\'ve already requested an email from us recently. To prevent email spam, you cannot request multiple times within a 10 minute window. Please check your inbox or wait 10 minutes and try again.');
								flowautho_set_form_error('mail', 'c-ate-resend-password-error-antispam', $msg);
								break;
							case '404':
								// TODO: get proper error codes from web service doc
								flowautho_set_form_error('mail', 'c-ate-resend-account-activation-email-unrecognized-email', t('Unrecognised e-mail address'));
								break;
							default:
								$msg = t('Sorry something went wrong while trying to fulfill your request. Please try again later');
								flowautho_set_message('c-ate-resend-account-activation-email-error-generic', $msg, 'error', true);
								watchdog('flowdeveloper','request account activation email unknown status  '.$resCode);
								break;
						}					
						
						
				} catch (Exception $e) {
					
					drupal_set_message('<div class="c-ate-resend-activation-email-error-generic">'.t("Failed to resend account activation e-mail.").'</div>', 'error');
					$form_state['redirect'] = '';
					return;
				}				
			}
			else
			{
				flowautho_set_form_error('mail', 'c-ate-resend-account-activation-email-unrecognized-email', t('Unrecognised e-mail address'));
			}
			

		}
	}
	else
	{
		flowautho_set_form_error('name', 'c-ate-resend-password-error-invalid-email', t( 'A valid e-mail address is required' ));
	}
}

function flowdeveloper_form_user_pass_submit($form, &$form_state)
{
	$form_state['redirect'] = '<front>';
	return;	
}

function flowdeveloper_form_user_profile_form_alter(&$form, &$form_state)
{
	global $user;
	
	if(($user->uid != 1) && flowautho_is_authentified())
	{
		unset($form['field_user_picture']);
		$form['current_email'] = array('#type' => 'hidden', '#value' => $user->mail);
		
		$form['account']['name']['#attributes']['class'][] = "c-ate-updateprofile-username";
		$form['account']['mail']['#attributes']['class'][] = "c-ate-updateprofile-email";
		$form['account']['current_pass']['#attributes']['class'][] = "c-ate-updateprofile-currentpassword";
		
		$form['account']['name']['#description'] = t('Use only letters, numbers, hyphens, underscores and periods.');
		$form['account']['current_pass']['#description'] = t('Enter your current password to change the E-mail address or Password');
		$form['account']['mail']['#description'] = '';
	
		$form['#validate'][] = 'flowdeveloper_form_user_profile_form_validate';
		$form['#submit'][] = 'flowdeveloper_form_user_profile_form_submit';
		
		$elementInfo = element_info('password_confirm');
		$elementInfo['#process'][] = '_flowdeveloper_process_password_confirm';
		$form['account']['pass']['#process'] = $elementInfo['#process'];
		
		$form['#after_build'][] = '_flowdeveloper_form_user_profile_form_after_build';
		
		$cmail = $form['account']['name']['#default_value'];
		$prefixe = '<div class="row c-current-email" data-cemail="'. $cmail .'">'
				 . '	<div class="col-xs-12 col-sm-5 col-lg-4">';
		$suffix  = '	</div>'
				 . '</div>';
		
		$form['#prefix'] = $prefixe;
		$form['#suffix'] = $suffix;
		
		
		//drupal_set_message('<pre>[flowdeveloper_form_user_profile_form_alter::] FormUPF:: '. print_r($form['account']['name'], true).'</pre>');
	}	
	
}


function _flowdeveloper_process_password_confirm($element)
{
	$element['pass1']['#attributes']['class'][] =  'c-ate-updateprofile-password';
	$element['pass2']['#attributes']['class'][] =  'c-ate-updateprofile-passwordconfirm';
	
	return $element;
}

function _flowdeveloper_form_user_profile_form_after_build($form_element, &$form_state)
{
	$form_element['timezone']['timezone']['#attributes']['class'][] = 'c-ate-updateprofile-timezone';
	$form_element['actions']['submit']['#attributes']['class'][] = 'c-ate-updateprofile-submit-button';
	
	//drupal_set_message('<pre>[flowdeveloper_form_user_profile_form_alter::] FormUPF:: '. print_r($form_element, true).'</pre>');
	
	return $form_element;
}

function flowdeveloper_form_user_profile_form_validate($form, &$form_state)
{
	global $user;
	
	$newPword =  $form_state['input']['pass']['pass1'];
	$newPwordConfirmed =  $form_state['input']['pass']['pass2'];
	
	$newPassword = $form_state['values']['pass'];
	$currentPassword = $form_state['values']['current_pass'];
	$newEmail = $form_state['values']['mail'];
	$newTimeZone = $form_state['values']['timezone'];
	$name = $form_state['values']['name']; 
	
	$validateCurrentPassword = false;
	$validationError = false;
	
	// clear previously set errors
	form_clear_error();
	// clear previously set error messages
	$emsgs = drupal_get_messages('error');
	
	
	//$usernameError = user_validate_name($name);
	$usernameError = _flowdeveloper_validate_username($name);
	if (strlen($usernameError) > 0) 
	{
		flowautho_set_form_error('name', 'c-ate-updateprofile-error-invalid-username', $usernameError);
		$validationError = true;
	}
	elseif (flowautho_username_already_exist($user->uid, $name))
	{
		$msg = t('Your chosen username is already taken. Please chose another one.');
		flowautho_set_form_error('name', 'c-ate-updateprofile-error-invalid-username', $msg);
		$validationError = true;
	}
	
	
	if (!filter_var($newEmail, FILTER_VALIDATE_EMAIL)) 
	{
		$msg = t('The e-mail address %mail is not valid.', array('%mail' => $newEmail));
		flowautho_set_form_error('mail', 'c-ate-updateprofile-error-invalid-email', $msg);
		$validationError = true;
	}
	
	if ($user->mail != $newEmail) 
	{
		/**
		 * 1. check if the new email is already taken
		 * 2. set validate password flag
		 */
		$existingUser = flowautho_drupal_knows_user($newEmail);
		if (isset($existingUser['uid'])) 
		{
			$msg = t('The e-mail address %mail has already been registered.', array('%mail' => $newEmail));
			flowautho_set_form_error('mail', 'c-ate-updateprofile-error-email-already-registered', $msg);
			$validationError = true;			
		}
		else
		{
			$validateCurrentPassword = true;
		}
	}
	
	if ((!empty($newPword)) || (!empty($newPwordConfirmed))) 
	{
		/**
		 * 1. Check password match
		 * 2. set validate password flag
		 */
		if ($newPword != $newPwordConfirmed) 
		{
			$msg =  t('The new password confirmation didn\'t match');
			flowautho_set_form_error('pass', 'c-ate-updateprofile-error-newpassword', $msg);
			$validationError = true;
		}
		elseif ( $msg = _flowdeveloper_validate_password($newPword))
		{
			flowautho_set_form_error('pass', 'c-ate-updateprofile-error-newpassword', $msg);
			$validationError = true;
		}
		else
		{
			$validateCurrentPassword = true;
		}
	}
	
	
	if ($validateCurrentPassword && (empty($currentPassword))) 
	{
		$msg =  t('Please enter your current password to change either your e-mail or password');
		flowautho_set_form_error('current_pass', 'c-ate-updateprofile-error-currentpassword', $msg);
		$validationError = true;		
	}
	elseif ($validateCurrentPassword && (!empty($currentPassword)))
	{
		try {
	  			$authoCredentials = flowautho_get_oauth_credentials($user->mail);
	  			/** @var FDWUserServicesImpl */
	  			$fdwUserServices = new FDWUserServicesImpl($authoCredentials, $user);
	  			if (!$fdwUserServices->validatePassword($currentPassword)) 
	  			{
	  				$msg = t('The value you entered for your current password is wrong.');
					flowautho_set_form_error('current_pass', 'c-ate-updateprofile-error-currentpassword', $msg);
					$validationError = true;
	  			}
			
		} catch (FDWUnknownUserException $e) {
			
			drupal_goto('user/login');
		}
	}
	
	
	/**
	 * If there was no validation error, update the user's FlowCloud account in this function 
	 * so that if there was an error, we can set a form error and prevent Drupal from 
	 * going ahead and updating the local account. Drupal is able to do this because 
	 * its submit function runs before our submit function. 
	 */
	if (!$validationError) 
	{
		/**
		 * Update account on condition that:
		 */
		if ( ($user->mail != $newEmail) || ((!empty($newPassword)) && ($newPassword != $currentPassword)) || (!empty($name)) ) 
		{
			
			try {
				
	  			$authoCredentials = flowautho_get_oauth_credentials($user->mail);
	  			//$authoCredentials = flowautho_get_oauth_credentials($newEmail);
	  			/** @var FDWUserServicesImpl */
	  			$fdwUserServices = new FDWUserServicesImpl($authoCredentials, $user);
	  			$flowCloudUser = $fdwUserServices->getUserPartial();
		
				//$userName =  $flowCloudUser['UserName'];
				$userName = $name;
				$oldPassword = ((!empty($newPassword)) && ($newPassword != $currentPassword)) ? $currentPassword : null; 
				$newPassword = (!empty($newPassword)) ? $newPassword : null; 
				$email = ($user->mail != $newEmail) ?  $newEmail : $flowCloudUser['Email']; 
				$title = (isset($flowCloudUser['Title'])) ? $flowCloudUser['Title'] : null; 
				$foreName = (isset($flowCloudUser['ForeName'])) ? $flowCloudUser['ForeName'] : null;
				$familyName = (isset($flowCloudUser['FamilyName'])) ? $flowCloudUser['FamilyName'] : null;
				$allowEmailCommunication =(isset($flowCloudUser['AllowEmailCommunication'])) ? $flowCloudUser['AllowEmailCommunication'] : null;  
				$allowDirectMarketing = (isset($flowCloudUser['AllowDirectMarketing'])) ? $flowCloudUser['AllowDirectMarketing'] : null;
				$locale	= 'en-GB';
				
				$responseContainer = $fdwUserServices->updateUserAccount(	$userName, 
																			$oldPassword, 
																			$newPassword, 
																			$email, 
																			$title, 
																			$foreName, 
																			$familyName, 
																			$allowEmailCommunication, 
																			$allowDirectMarketing, 
																			$locale);

				if ($responseContainer['updated']) 
				{
					// do nothing				
				}
				elseif ( in_array('UserName', $responseContainer['invalid_fields']) ||  in_array('Email', $responseContainer['invalid_fields']) )
				{
					$msg = t('This username is already taken. Please choose another one.');
					flowautho_set_form_error('name', 'c-ate-updateprofile-error-username-already-exists', $msg);
				}
				elseif ( in_array('Password', $responseContainer['invalid_fields']))
				{
					$msg = t('Your new password is not valid, please choose another one.');
					flowautho_set_form_error('pass', 'c-ate-updateprofile-error-invalid-password', $msg);				
				}
				else
				{
					$msg = t('An error occured while we were trying to update your account! Please try again later.');
					flowautho_set_form_error(' ', 'c-ate-updateprofile-error-unknown-error', $msg);		
				}
																			
				
			} catch (FDWUnknownUserException $e) {
				
				$msg = t('An error occured while we were trying to update your account! Please try again later.');
				flowautho_set_form_error(' ', 'c-ate-updateprofile-error-unknown-error', $msg);
				
			}
		}
	}
	
	
	//flowautho_set_form_error('mail', 'c-ate-updateprofile-error-invalid-email', 'Dev Error Message');
	//drupal_set_message('<pre>[flowdeveloper_form_user_profile_form_validate::] Form:: '. print_r($form_state, true).'</pre>');	
}

function flowdeveloper_form_user_profile_form_submit($form, &$form_state)
{
	global $user;
	
	if (flowautho_is_authentified()) 
	{
		if($user->mail != $form_state['values']['mail'])
		{
			$form_state['redirect'] = 'user/logout';
		}
		else 
		{
			$smsgs = drupal_get_messages('status');
			$msg = t('Your account was successfully updated.');
			flowautho_set_message('c-ate-updateprofile-success', $msg, 'status');							
		}
	}
	
	//drupal_set_message('<pre>[flowdeveloper_form_user_profile_form_submit::]</pre>');
	//drupal_set_message('<pre>[flowdeveloper_form_user_profile_form_submit::] Form:: '. print_r($form_state['values'], true).'</pre>');	
}


function _flowdeveloper_form_user_login_form_after_build($form_element, &$form_state)
{
	if (array_key_exists('persistent_login', $form_element)) 
	{
		$form_element['persistent_login']['#attributes']['class'][] = 'c-ate-login-remember-me q-rememberme';
		$form_element['persistent_login']['#title'] = 'Stay signed in';
		$form_element['persistent_login']['#weight'] = 200;
	}
	
	return $form_element;
}


function _flowdeveloper_form_user_register_form_after_build($form_element, &$form_state)
{
	/**
	 * Unset persistent window checkbox for the registration page
	 */
	if (isset($form_element['account']['persistent_login'])) 
	{
		unset($form_element['account']['persistent_login']);
	}
	
	
	return $form_element;
}
