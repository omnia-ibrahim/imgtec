<?php

// $Id: sandwich.drush.inc,v 1.1 2010/04/22 19:37:56 weitzman Exp $

/**
 * @file
 *   Example drush command.
 *
 *   To run this *fun* command, execute `sudo drush --include=./examples mmas`
 *   from within your drush directory.
 *
 *   Shows how to make your own drush command.
 *
 *   You can copy this file to any of the following
 *     1. A .drush folder in your HOME folder.
 *     2. Anywhere in a folder tree below an active module on your site.
 *     3. /usr/share/drush/commands (configurable)
 *     4. In an arbitrary folder specified with the --include option.
 */

/**
 * Implementation of hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function flowdeveloper_drush_command() 
{
  $items = array();

  $items['flowdeveloper-importuser'] = array(
	  'description' => "Adds an existing webservice user to the drupal database",
	  'aliases' => array('fdiu'),
	  'arguments' => array(
						  'userid' => 'UserId of a user that already exists in the webservice',
					      'mail' => 'Email address',
					      'name' => 'Username',
					      'pass' => 'Password',
					      'licenseeid' => 'LicenseeID'
	  						),
  );

  return $items;
}

function drush_flowdeveloper_importuser($userid=null, $mail=null, $name=null, $pass=null, $licenseeid=null) {

  #global $user = $_account;
	/**
	 * Call the plugin as follows:
	 * 
	 *  drush fdiu 5a16c376-3b31-4d5a-9a75-0b621ae87190 murat0@outlook.com murat0@outlook.com Pass458word$ 17
	 *  
	 */	
  if( $userid && $mail && $name && $pass && $licenseeid)
  {
  	$account = new stdClass();
	$account->is_new = true;  	
	
	$edit['name'] = $name;
	$edit['mail'] = $mail;
	$edit['pass'] = $pass;
	$edit['init'] = $userid;
	$edit['status'] = 1;
	$edit['language'] = 'en';
	
	$data['licensee_id'] = $licenseeid;
	$data['lounge2_guid'] = $userid;
	$edit['data'] = $data;

	$account = user_save($account, $edit);
	/**  	
    $_account['mail'] = $mail;
    $_account['pass'] = $pass;
    $_account['init'] = $userid;
    $_account['name'] = $name;
    $_account['status'] = 1;
    $_account['licensee_id'] = $licenseeid;
    $_account['lounge2_guid'] = $userid;

    $_user = user_save(NULL, $_account); // update user account
    **/
    print_r($account);
  }
  else
  {
    return drush_set_error('INVALID_ARGUMENTS', dt('Hey, you\'re missing some arguments, init?  Run "drush help fdiu"' ));
  }
}

