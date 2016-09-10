<?php	
	//$resourceObjects = $variables['resourceObjects'];
	//$deviceID = $variables['deviceID'];
	
		if (isset($resourceObjects) && (count($resourceObjects) > 0))
		{  
			$k = 0;
			foreach ($resourceObjects as $ro) 
			{
				$k++;
				$roATEClass = 'c-ate-resource-object-'.$k;
				$instanceCount = count($ro['Instances']);
				$themedInstances = '';
				if ($instanceCount > 1) 
				{
					$instances = $ro['Instances'];
					$i = 0;
					foreach ($instances as $instance)
					{
						$i++;
						$last = ($i == $instanceCount) ? ' q-last c-ate-resource-instance-'.$i.' ' : ' c-ate-resource-instance-'.$i.' ';
						$args = array('extraClasses' => $last, 'instanceID' => $instance['InstanceID'], 'objectID' =>  $ro['ObjectID'], 'deviceID' => $deviceID, 'instanceCount' => $instanceCount);
						$themedInstances .= theme('flowdeveloper_device_resource_instance_list_item', $args); 
					}
?>
					<!-- Content -->
					<div class="c-resource-object q-multiple c-ate-multiple-instances row <?php print $roATEClass ?>" data-roid="<?php print $ro['ObjectID']; ?>"  data-deviceid="<?php print $deviceID; ?>">
						<div class="c-header-wrapper col-xs-12">
							<div class="c-header row">
								<div class="cp-name col-xs-9 col-md-11"><?php print $ro['Name']; ?></div>
								<div class="cp-resource-meta col-xs-3 col-md-1">
									<span class="cp-dcount"><?php print $instanceCount; ?></span><span class="cp-icon"></span>
								</div>
							</div>
						</div>
						<div class="cp-instances col-xs-12">
							<?php	print $themedInstances;	?>	
						</div>
					</div>
<?php
				}
				elseif ($instanceCount == 1)
				{
?>
					<!-- Content -->
					<div class="c-resource-object  q-single c-ate-single-instance row <?php print $roATEClass ?>" data-roid="<?php print $ro['ObjectID']; ?>"  data-iid="<?php print $ro['Instances'][0]['InstanceID']; ?>" data-deviceid="<?php print $deviceID; ?>">
						<div class="c-header-wrapper col-xs-12">
							<div class="c-header row">
								<div class="cp-name col-xs-9 col-md-11"><?php print $ro['Name']; ?></div>
								<div class="cp-resource-meta col-xs-3 col-md-1">
									<span class="cp-dcount">&nbsp;</span><span class="cp-icon"></span>
								</div>
							</div>
						</div>
						<div class="cp-instances col-xs-12">
							<?php
								$args = array(
										'extraClasses'=> ' q-last c-ate-resource-instance-1', 
										'instanceID'=> $ro['Instances'][0]['InstanceID'], 
										'objectID'=> $ro['ObjectID'], 
										'deviceID'=> $deviceID,
										'instanceCount' => 1
								);
								$singleInstance = theme('flowdeveloper_device_resource_instance_list_item', $args);
								print $singleInstance;
							?>
						</div>
					</div>					
<?php 					
				}
				else
				{
?>		
					<!-- Content -->
					<div class="c-resource-object  q-none c-ate-no-instances row <?php print $roATEClass ?>" data-roid="<?php print $ro['ObjectID']; ?>"  data-deviceid="<?php print $deviceID; ?>">
						<div class="c-header-wrapper col-xs-12">
							<div class="c-header row">
								<div class="cp-name col-xs-9 col-md-11"><?php print $ro['Name']; ?></div>
								<div class="cp-resource-meta col-xs-1 col-md-1">
									<span class="cp-dcount"></span><span class="cp-icon"></span>
								</div>
							</div>
						</div>
					</div>
<?php 
				}
				
			} //end-foreach	
		}
		else 
		{
?>
			<p><?php print t('There are currently no resource objects available for this device'); ?></p>		
		
<?php	
		}	
?>		
		

