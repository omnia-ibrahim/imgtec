<?php

/**
 * @file
 * This file will house licensee related theme implementations  
 */


function theme_flowdeveloper_licensee_list($variables)
{
	$licensees = $variables['licensees'];
	$output = '<p>'
			.	t('There are currently no licensees in the system.')
			. '</p>';
	
	if (is_array($licensees) && (count($licensees) > 0)) 
	{
		$tableBody = '';
		$tableRow = '';
		$rowCount = 0;
		
		foreach ($licensees as $licensee) 
		{
			$rowCount++;
			$rowClass = (($rowCount%2) > 0) ? 'odd' : 'even';
			$tableRow = '<tr class="'.$rowClass.'">'
					  . '	<td>' . $licensee['licensee_id']. '</td>'
					  . '	<td>' . $licensee['licensee_name'] . '</td>'
					  . '	<td>' . $licensee['oauth_key']. '</td>'
					  . '	<td>' . $licensee['oauth_secret'] . '</td>'
					  . '	<td>' . flowdeveloper_decode_licensee_visibility_status($licensee['visibility']) . '</td>'					  
					  . '	<td></td>'					  
					  . '</tr>';
					  
			$tableBody .= $tableRow;			
		}
		
		$output = '<p>' . t('Currently registered licensees') . '</p>'
				. '<table>'
				. '	<thead>'
				. '		<tr>'
				. '			<th>' . t('Licensee ID') . '</th>'
				. '			<th>' . t('Name') . '</th>'
				. '			<th>' . t('OAuth Key') . '</th>'
				. '			<th>' . t('OAuth Secret') . '</th>'
				. '			<th>' . t('Visibility') . '</th>'				
				. '			<th>' . t('Action') . '</th>'				
				. '		</tr>'
				. ' 	</thead>'
				. '	<tbody>'
				. $tableBody
				. '	</tbody>'	
				. '</table>'; 		
	}
	
	return $output;
	
}