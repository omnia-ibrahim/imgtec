<div>
	<!-- Nav tabs -->
	<ul class="nav nav-tabs" role="tablist">
		<li class="c-device-tab active" role="presentation">
			<a class="c-ate-device-detail-status-tab c-no-refresh" href="#device-status" aria-controls="device-status" role="tab" data-toggle="tab">Status</a>
		</li>
		<li class="c-device-tab" role="presentation">
			<a class="c-ate-device-detail-info-tab c-no-refresh" href="#device-info" aria-controls="device-info" role="tab" data-toggle="tab">&nbsp;Info&nbsp;</a>
		</li>
		<li class="c-device-tab" role="presentation">
			<a class="c-ate-device-detail-resources-tab c-no-refresh" href="#device-resources" aria-controls="device-resources" role="tab" data-toggle="tab">&nbsp;Resources&nbsp;</a>
		</li>
	</ul>

	<!-- Tab panes -->

	<div class="tab-content">
	
		<!-- New Status tab -->
		<div role="tabpanel" class="tab-pane active" id="device-status">
			<div class="c-tab-content-group q-status row">
			
				<?php if (isset($device['IsManagable']) && $device['IsManagable']){ //	MANAGED DEVICES ?>
				
					<div class="c-status-group q-power-sources col-xs-12">
						<div class="cn-row-wrapper row">
							<div class="cp-header col-xs-12">Power Information</div>
						</div>
						<div class="cn-row-wrapper row">
							<div class="cp-description col-xs-12"><?php print t('You can find power related information below.'); ?></div>
						</div>
						<div class="cp-content row">
							<?php 
								if (isset($status['PowerSources']) && count($status['PowerSources'])) {
									foreach ($status['PowerSources'] as $powerSource) {
										
										$themedPowerSource = theme('flowdeveloper_device_powersource', array('powerSource' => $powerSource));
										print $themedPowerSource;
							?>
							
							<?php 
								 	}
								}
							?>
						</div>				
					</div>
					
					<!--  <div class="c-status-group q-spacer hidden-xs hidden-sm hidden-md col-lg-1">&nbsp;</div>-->
					
					<div class="c-status-group q-storage col-xs-12">
						<div class="cn-row-wrapper row">
							<div class="cp-header col-xs-12">Storage</div>
						</div>
						<div class="cn-row-wrapper row">
							<div class="cp-description col-xs-12"><?php print t('Amount of used and available storage.'); ?></div>
						</div>
						<div class="cp-content row">
							<?php
									if (isset($status['NormalizedStorageInfo']) &&  count($status['NormalizedStorageInfo'])) {
										foreach ($status['NormalizedStorageInfo'] as $storageItem) {
											$themedStorageItem = theme('flowdeveloper_device_storage', array('storageItem' => $storageItem));
											print $themedStorageItem; 
										}
									} 
							?>
						</div>				
					</div>
					
					<div class="c-status-group q-location col-xs-12">
						<div class="cn-row-wrapper row">
							<div class="cp-header col-xs-12">Location</div>
						</div>
						<div class="cn-row-wrapper row">
							<div class="cp-description col-xs-12"><?php print t('The current location of your device.'); ?></div>
						</div>
						<div class="cp-content row">
						<?php 
							if (isset($locations) && count($locations) && isset($locations['GeoLocation'])) 
							{
								$themedGeLocation = theme('flowdeveloper_device_geolocation', array('locationData' => $locations['GeoLocation']));
								print $themedGeLocation;
							}	
						?>
						</div>				
					</div>
					
					<!--  <div class="c-status-group q-spacer hidden-xs hidden-sm hidden-md col-lg-1">&nbsp;</div>-->	
						
									
				<?php }else{	//UNMANAGED DEVICES ?>
				
					<div class="c-no-status col-xs-12"><?php print t('The status of your device cannot be retrieved because it is not a managed device .'); ?></div>
					
				<?php }?>
				
			</div>
		</div>
		
		<div role="tabpanel" class="tab-pane" id="device-info">
			<div class="c-tab-content-group">
				<div class="c-tab-header">
					Identification
					<button id="c-tab-device-edit-icon" class="c-tab-edit-icon pull-right c-ate-device-detail-info-edit c-no-refresh">Edit</button>
				</div>

				<div class="c-tab-description">
					You can identify your board by giving it a name and a description.
				</div>

				<div class="c-tab-actual-content">
					<div class="c-device-detail-row row">
						<div class="c-device-name-field-title col-md-2 col-lg-1">
							<?php print t('Name'); ?>
						</div>
						<div class="c-device-name-field-value c-ate-device-detail-name col-xs-8 col-lg-10"><?php print $device['DeviceName']; ?></div>
					</div>

					<div class="c-device-detail-row row">
						<div class="c-device-description-field-title col-md-2 col-lg-1">
							<?php print t('Description'); ?>
						</div>
						<div class="c-device-description-field-value c-ate-device-detail-desc col-xs-8 col-lg-10"><?php print $device['Description']; ?></div>
					</div>

					<div class="c-device-detail-row row">
						<div class="c-device-detail-edit-btns col-md-offset-4">
							<button class="c-device-detail-edit-cancel c-ate-device-detail-edit-cancel c-no-refresh">Cancel</button>
							<button disabled class="c-device-detail-edit-update c-ate-device-detail-edit-update disabled" data-device-id="<?php print $device['DeviceID']; ?>">Update</button>
						</div>
					</div>
				</div>
			</div>
			<div class="c-tab-content-group">
				<div class="c-tab-header">
					Details
				</div>

				<div class="c-tab-description">
					The core device management information about the device.
				</div>

				<div class="c-tab-actual-content">
					<?php if ($device['DeviceID']): ?>
						<div class="c-device-detail-row row">
							<div class="c-device-detail-field-title col-md-2 col-lg-1">
								<?php print t('ID'); ?>
							</div>
							<div class="c-device-detail-field-value c-ate-device-detail-id col-md-10 col-lg-11">
								<?php print $device['DeviceID']; ?>
							</div>
						</div>
					<?php endif; ?>
					<?php if ($device['DeviceType']): ?>
						<div class="c-device-detail-row row">
							<div class="c-device-detail-field-title col-md-2 col-lg-1">
								<?php print t('Type'); ?>
							</div>
							<div class="c-device-detail-field-value c-ate-device-detail-devicetype col-md-10 col-lg-11">
								<?php print $device['DeviceType']; ?>
							</div>
						</div>
					<?php endif; ?>
					<?php if ($device['Manufacturer']): ?>
						<div class="c-device-detail-row row">
							<div class="c-device-detail-field-title col-md-2 col-lg-1">
								<?php print t('Manufacturer'); ?>
							</div>
							<div class="c-device-detail-field-value c-ate-device-detail-manufacturer col-md-10 col-lg-11">
								<?php print $device['Manufacturer']; ?>
							</div>
						</div>
					<?php endif; ?>
					<?php if ($device['CreatedDate']): ?>
						<div class="c-device-detail-row row">
							<div class="c-device-detail-field-title col-md-2 col-lg-1">
								<?php print t('Created date'); ?>
							</div>
							<div class="c-device-detail-field-value c-ate-device-detail-created col-md-10 col-lg-11">
								<?php print $device['CreatedDate']; ?>
							</div>
						</div>
					<?php endif; ?>
					<?php if ($device['MACAddress']): ?>
						<div class="c-device-detail-row row">
							<div class="c-device-detail-field-title col-md-2 col-lg-1">
								<?php print t('MAC address'); ?>
							</div>
							<div class="c-device-detail-field-value c-ate-device-detail-created col-md-10 col-lg-11">
								<?php print $device['MACAddress']; ?>
							</div>
						</div>
					<?php endif; ?>
					<?php if ($device['SerialNumber']): ?>
						<div class="c-device-detail-row row">
							<div class="c-device-detail-field-title col-md-2 col-lg-1">
								<?php print t('Serial Number'); ?>
							</div>
							<div class="c-device-detail-field-value c-ate-device-detail-serial col-md-10 col-lg-11">
								<?php print $device['SerialNumber']; ?>
							</div>
						</div>
					<?php endif; ?>
					<?php if ($device['ModelNumber']): ?>
						<div class="c-device-detail-row row">
							<div class="c-device-detail-field-title col-md-2 col-lg-1">
								<?php print t('Model Number'); ?>
							</div>
							<div class="c-device-detail-field-value c-ate-device-detail-model col-md-10 col-lg-11">
								<?php print $device['ModelNumber']; ?>
							</div>
						</div>
					<?php endif; ?>
					<?php if ($device['SoftwareVersion']): ?>
						<div class="c-device-detail-row row">
							<div class="c-device-detail-field-title col-md-2 col-lg-1">
								<?php print t('Software'); ?>
							</div>
							<div class="c-device-detail-field-value c-ate-device-detail-softwareversion col-md-10 col-lg-11">
								<?php print $device['SoftwareVersion']; ?>
							</div>
						</div>
					<?php endif; ?>
					<?php if ($device['FirmwareVersion']): ?>
						<div class="c-device-detail-row row">
							<div class="c-device-detail-field-title col-md-2 col-lg-1">
								<?php print t('Firmware'); ?>
							</div>
							<div class="c-device-detail-field-value c-ate-device-detail-firmwareversion col-md-10 col-lg-11">
								<?php print $device['FirmwareVersion']; ?>
							</div>
						</div>
					<?php endif; ?>
					<?php if ($device['HardwareVersion']): ?>
						<div class="c-device-detail-row row">
							<div class="c-device-detail-field-title col-md-2 col-lg-1">
								<?php print t('Hardware'); ?>
							</div>
							<div class="c-device-detail-field-value c-ate-device-detail-hardwareversion col-md-10 col-lg-11">
								<?php print $device['HardwareVersion']; ?>
							</div>
						</div>
					<?php endif; ?>
				</div>

			</div>
			<div class="c-tab-content-group">
				<div class="c-tab-header">Capabilities</div>
				<div class="c-tab-description">A list of the device's capabilities.</div>
				<div class="c-tab-actual-content">
					<?php	
							if(isset($device['Capabilities']) && count($device['Capabilities'])){
								$i=0;
								foreach ($device['Capabilities'] as $capability) {
									$i++;	 
					?>
					<div class="c-device-detail-row row">
						<div class="c-ate-device-capability col-xs-12"><?php print $i.'. '.$capability; ?></div>
					</div>
					<?php 
								}
							}	
					?>
				</div>
			</div>
		</div>
		<div role="tabpanel" class="tab-pane" id="device-resources">
			<div class="c-tab-content-group">
				<!--  <div class="c-tab-header">
					Resource Objects
				</div>-->
				<div class="c-tab-actual-content">
					<?php print $resources; ?>
				</div>
				
			</div>
		</div>
	</div>

</div>
