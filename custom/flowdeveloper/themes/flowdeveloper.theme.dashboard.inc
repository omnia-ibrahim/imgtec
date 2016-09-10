<?php


/**
 * Preprocess variables for the registered devices template
 * 
 * @param array $variables
 */
function template_preprocess_flowdeveloper_dashboard_registered_devices(&$variables)
{
	$primaryMetric = 0;
	$secondaryMetric = 0;
	$regDevicesMetrics = $variables['regDevicesMetrics'];
	
	$variables['primaryMetric'] = $primaryMetric;
	$variables['secondaryMetric'] = $secondaryMetric;
	
	$dataAvailable = (isset($regDevicesMetrics) && is_array($regDevicesMetrics)) ? true : false;
	
	if (flowdeveloper_is_licensee_admin()) 
	{
		$variables['isLicenseeAdmin'] = true;
		if ($dataAvailable) 
		{
			$variables['primaryMetric'] = $regDevicesMetrics['total'];
			$variables['secondaryMetric'] = $regDevicesMetrics['today'] . ' devices today<br/>'
										  . $regDevicesMetrics['month'] . ' devices this month<br/>';	
		}
	}
	else
	{
		$variables['isLicenseeAdmin'] = false;
		$variables['primaryMetric'] = ($dataAvailable) ? $regDevicesMetrics['total'] : $primaryMetric;
	} 
}


function theme_flowdeveloper_db_registered_devices_by_type($variables)
{
	$output = '<div class="c-db-right-col col-xs-12 col-md-6">'
			. '	<div class="c-reg-devices-by-type c-component">'
			. '		<div class="c-header">Registered Devices By Type</div>'
			. '		<div id="reg-devices-bytype-chart" class="c-content">'
			. '			<div class="c-ajax-preloader"></div>'
			. '		</div>'
			. '	</div>'	
			. '</div>';

	return $output;
}

function theme_flowdeveloper_db_connected_devices($variables)
{
	$output = '<div class="c-connected-devices c-component col-xs-12">'
			. '	<div class="c-drill-down-trigger q-connected-devices" data-title="Connected Devices over time"></div>'
			. '	<div class="c-header">Connected Devices for the last 30 days</div>'
			. '	<div id="connected-devices-chart" class="c-content">'
			. '		<div class="c-ajax-preloader"></div>'
			. '	</div>'
			. '</div>';

	return $output;	
}

function theme_flowdeveloper_db_firmware_device_count($variables)
{
	$output = '<div class="c-db-left-col col-xs-12 col-md-6">'
			. '	<div class="c-firmware-versions-count c-component">'
			. '		<div class="c-header">Firmware Versions</div>'
			. '		<div class="c-content">0</div>' 			
			. '	</div>'
			. '</div>';

	return $output;		
}

function theme_flowdeveloper_db_devices_by_firmware($variables)
{
	/**
	$output = '<div class="c-devices-by-firmware-version c-component col-xs-12 col-md-6">'
			. '	<div class="c-drill-down-trigger q-firmware-versions" data-title="Device Firmware by Device Types"></div>'		
			. '	<div class="c-header">Device Firmware by Device Types</div>'
			. '	<div id="devices-by-firmware-version-chart" class="c-content">'
			. '		<div class="c-ajax-preloader"></div>'
			. '	</div>'
			. '</div>';
	**/
			
	$output = '<div class="c-db-right-col col-xs-12 col-md-6">'
			. '	<div class="c-devices-by-firmware-version c-component">'
			. '		<div class="c-drill-down-trigger q-firmware-versions" data-title="Device Firmware by Device Types"></div>'		
			. '		<div class="c-header">Device Firmware by Device Types</div>'
			. '		<div id="devices-by-firmware-version-chart" class="c-content">'
			. '			<div class="c-ajax-preloader"></div>'
			. '		</div>'
			. '	</div>'
			. '</div>';			

	return $output;	
}

function theme_flowdeveloper_db_connected_devices_bandwidth_metrics($variables)
{
	$output = '<div class="c-devices-bandwidth c-component col-xs-12">'
			. '	<div class="c-drill-down-trigger q-connected-devices-bandwidth" data-title="Devices Bandwidth usage over time in Kilobytes(KB)"></div>'
			. '	<div class="c-header">Device Bandwidth usage for the last 30 days in Kilobytes(KB)</div>'
			. '	<div id="devices-bandwidth-chart" class="c-content">'
			. '		<div class="c-ajax-preloader"></div>'
			. '	</div>'
			. '</div>';

	return $output;		
}

/**
 * @deprecated
 */
function theme_flowdeveloper_device_resources($variables)
{
	$resourceObjects = $variables['resourceObjects'];
	$deviceID = $variables['deviceID'];
	$output = '';
	
	if (isset($resourceObjects) && (count($resourceObjects) > 0)) 
	{
		
		foreach ($resourceObjects as $ro) 
		{
			$instanceCount = count($ro['Instances']);
			$themedInstances = '';
			if ($instanceCount > 1) 
			{
				$instances = $ro['Instances'];
				$i = 0;
				foreach ($instances as $instance) 
				{
					$i++;
					$last = ($i == $instanceCount) ? ' q-last ': ''; 
					$themedInstances .='<div class="c-resource-instance col-xs-12 '. $last .'" data-iid="'. $instance['InstanceID'] .'" data-deviceid="'. $deviceID .'" data-roid="'. $ro['ObjectID'] .'">'
									  .'	<div class="cp-icon s-collapsed col-xs-1"></div>'	
									  .'	<div class="cp-name col-xs-11">Instance '. $instance['InstanceID'] . '</div>'
									  .'	<div class="cp-details">'
									  .'		<div class="cp-icon col-xs-1"></div>'
									  .'		<div class="cp-content col-xs-11"></div>'
									  . '	</div>'
									  .'</div>';	
				}
				
				$themedObject = '<div class="c-resource-object row q-multiple" data-roid="'. $ro['ObjectID'] .'" data-deviceid="'. $deviceID .'">'
							  . '	<div class="cp-icon s-collapsed col-xs-1"></div>'	
							  . '	<div class="cp-name col-xs-9 col-sm-7">'. $ro['Name'] . '</div>'
							  . '	<div class="cp-dcount col-xs-6 col-sm-4">'. $instanceCount .' instances</div>'
							  . '	<div class="cp-instances row">'
							  . 		$themedInstances
							  . '	</div>'	
							  . '</div>';	
			}
			elseif ($instanceCount == 1)
			{
				
				$themedObject = '<div class="c-resource-object q-single row" data-roid="'. $ro['ObjectID'] .'" data-iid="'.$ro['Instances'][0]['InstanceID'].'" data-deviceid="'. $deviceID .'">'
							  . '	<div class="cp-icon s-collapsed col-xs-1"></div>'	
							  . '	<div class="cp-name col-xs-9 col-sm-7">'. $ro['Name'].'</div>'
							  . '	<div class="cp-dcount col-xs-6 col-sm-4">Instance 0</div>'
							  . '	<div class="cp-instances row">'
							  . 		'<div class="c-resource-instance col-xs-12 '. $last .'" data-iid="'. $ro['Instances'][0]['InstanceID'] .'" data-deviceid="'. $deviceID .'" data-roid="'. $ro['ObjectID'] .'">'
							  .'			<div class="cp-icon s-collapsed col-xs-1"></div>'	
							  .'			<div class="cp-name col-xs-11">Instance 0</div>'
							  .'			<div class="cp-details">'
							  .'				<div class="cp-icon col-xs-1"></div>'
							  .'				<div class="cp-content col-xs-11"></div>'
							  . '			</div>'							  
							  . '		</div>'
							  . '	</div>'	
							  . '</div>';				
			}
			else 
			{
				
				$themedObject = '<div class="c-resource-object q-none row" data-roid="'. $ro['ObjectID'] .'">'
							  . '	<div class="cp-icon col-xs-1"></div>'	
							  . '	<div class="cp-name col-xs-9 col-sm-7">'. $ro['Name'].'</div>'
							  . '	<div class="cp-dcount col-xs-6 col-sm-4">No instances</div>'
							  . '</div>';					
			}
			
			$output .= $themedObject; 
		}
	}
	else
	{
		$output = '<p>There are currently no resource objects available for this device</p>';
	}
	
	return $output;
}

function theme_flowdeveloper_resource_instance($variables)
{
	$resourceInstance = $variables['resourceInstance'];
	$objectID = $variables['objectID'];
	$instanceID = $variables['instanceID'];
	$output = '';
	
	$instanceNames = array_keys($resourceInstance['Properties']);
	if (count($instanceNames) == 1) 
	{
		$instanceName = $instanceNames[0];
		$instanceProperties = $resourceInstance['Properties'][$instanceName];
		$themedProperties = '';
		foreach ($instanceProperties as $key => $value) 
		{
			$themedProperties .= theme_flowdeveloper_resource_instance_property($key, $value);
		}
						
		$output = '	<div class="c-refresh-instance col-xs-12">'
				. '		<div class="c-ate-refresh-resource-instance-btn c-refresh-resource-instance-btn">'
				. '			<div class="cp-icon"></div><div class="cp-label">Refresh</div>'
				. '		</div>'
				. '	</div>'
				. '	<div class="cp-property c-ate-property row">'
				. '		<div class="cp-name c-ate-propertyname-ObjectID col-xs-12 col-sm-4 col-md-2">Object ID</div>'
				. '		<div class="cp-values c-ate-propertyvalue col-xs-12 col-sm-8 col-md-10">'. $objectID .'</div>'
				. '	</div>'
				. '	<div class="cp-property c-ate-instance-property row">'
				. '		<div class="cp-name c-ate-propertyname-ObjectInstanceID col-xs-12 col-sm-4 col-md-2">Object Instance ID</div>'
				. '		<div class="cp-values c-ate-propertyvalue col-xs-12 col-sm-8 col-md-10">'. $instanceID .'</div>'
				. '	</div>'				
				. 	$themedProperties;
	}
	
	return $output;
	
}

function theme_flowdeveloper_resource_instance_property($propertyName, $value)
{
	$output = '';
	
	if (isset($propertyName) && isset($value)) 
	{
		if (flowdeveloper_resource_instance_is_value_list($value)) 
		{
			$values = theme_flowdeveloper_resource_instance_property_value_list($value);
		}
		else
		{
			$values = $value;
		}

		$ateclassPropertyName = 'c-ate-propertyname-'.$propertyName;
		$output = '<div class="cp-property row c-ate-instance-property">'
				. '	<div class="cp-name '. $ateclassPropertyName .' col-xs-12 col-sm-4 col-md-2">'. $propertyName .'</div>'
				. '	<div class="cp-values c-ate-propertyvalue col-xs-12 col-sm-8 col-md-10">'. $values .'</div>'
				. '</div>';		
	}
	
	return $output;
}

function theme_flowdeveloper_resource_instance_property_value_list(array $valueList)
{
	$output = '';

	if (isset($valueList)) 
	{
		foreach ($valueList as $valueArray) 
		{
			$tkeys = array_keys($valueArray);
			$key = $tkeys[0];
			$output .= $valueArray[$key] .', ';
		}
	}
	
	return $output;
}

/**
 * This is not a themeing function in its own right but it is aa vital utility function for the resource instance themeing function.
 * 
 * This function  checks to see if a resource instance property array is a list of the same properties or is made up of more complex objects
 * @param string $propertyValue
 */
function flowdeveloper_resource_instance_is_value_list($propertyValue)
{
	$isList = false;
	if (isset($propertyValue) && is_array($propertyValue)) 
	{
		/**
		 * Ensure that the array is indexed
		 */
		$topLevelKeys = array_keys($propertyValue);
		$isIndexed = true;
		foreach ($topLevelKeys as $key) 
		{
			if (!is_numeric($key)) 
			{
				$isIndexed = false;
				break;
			}
		}
		
		if ($isIndexed) 
		{
			/**
			 * Extract the first key from the first array which is supposed to be a list item
			 */
			$tempArray = $propertyValue[0];
			$tempKeys = array_keys($tempArray);
			
			if (count($tempKeys) == 1) 
			{
				$candidateKey = $tempKeys[0];
				$unEqualElmentFound = false;
				
				foreach ($propertyValue as $valueArray) 
				{
					$tkeys = array_keys($valueArray);
					if (!((count($tkeys) == 1) && ($tkeys[0] == $candidateKey))) 
					{
						$unEqualElmentFound = true;
						break;
					}
				}
				
				if (!$unEqualElmentFound) 
				{
					$isList = true;
					//_flowautho_debug('[flowdeveloper_resource_instance_is_value_list:: ] Is Property List: ');
				}
			}
		}
	}
	
	return $isList;
}