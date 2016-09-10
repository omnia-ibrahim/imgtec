<?php
/**
 * @file
 * This file houses licensee related forms and utility functions
 */

/**
 * Returns an array of FlowCloud licensees.
 * 
 * Each licensee is represented in an associative array. The array keys for each licensee entry are:
 * 
 * - licensee_id
 * - licensee_name
 * - oauth_key
 * - oauth_secret
 * - visibility
 * 
 * @return array 
 */
function flowdeveloper_get_licensee_list()
{
	$licensees = array();
	$sqlQuery = 'SELECT licensee_id, licensee_name, oauth_key, oauth_secret, visibility FROM {flowdeveloper_licensee}';
	$resultSet = db_query($sqlQuery);

	while ($row = $resultSet->fetchAssoc()) 
	{
		$licensees[] = array(
							'licensee_id' => $row['licensee_id'],
							'licensee_name' => $row['licensee_name'],
							'oauth_key' => $row['oauth_key'],
							'oauth_secret' => $row['oauth_secret'],
							'visibility' => $row['visibility'] 
						);
	}
	
	return $licensees;
}

/**
 * Returns a text representation of the visibility status
 * 
 * @param int $visStatus
 * @return string
 */
function flowdeveloper_decode_licensee_visibility_status($visStatus)
{
	$vs = null;
	if ($visStatus == FLOWDEVEL_LVISIBILITY_VISIBLE) 
	{
		$vs = 'Public';
	}
	elseif ($visStatus == FLOWDEVEL_LVISIBILITY_HIDDEN)
	{
		$vs = 'Private';
	}
	return $vs;
}

/**
 * Return a licensee record identified by the supplied identifier
 * 
 * @param int $licenseeId
 * @param boolean $private
 * @return array
 */
function flowdeveloper_find_a_licensee_by_id($licenseeId,  $private=true)
{
	$licensee = array();
	if (isset($licenseeId)) 
	{
		if(is_null($private))
		{
			$sqlQuery = "SELECT licensee_id, licensee_name, oauth_key, oauth_secret FROM {flowdeveloper_licensee} WHERE licensee_id = :lid";
			$resultSet = db_query($sqlQuery, array(':lid' => $licenseeId));
		}
		else
		{
			$visibility = ($private) ? 0 : 1;
			$sqlQuery = "SELECT licensee_id, licensee_name, oauth_key, oauth_secret FROM {flowdeveloper_licensee} WHERE visibility = :vis and licensee_id = :lid";
			$resultSet = db_query($sqlQuery, array(':vis' => $visibility, ':lid' => $licenseeId));
		}
		
		if($recordSet = $resultSet->fetchAssoc()) 
		{
			$licensee['licensee_id'] = $recordSet['licensee_id'];
			$licensee['licensee_name'] = $recordSet['licensee_name'];
			$licensee['oauth_key'] = $recordSet['oauth_key'];
			$licensee['oauth_secret'] = $recordSet['oauth_secret'];
		}
	}
	return $licensee;	
}