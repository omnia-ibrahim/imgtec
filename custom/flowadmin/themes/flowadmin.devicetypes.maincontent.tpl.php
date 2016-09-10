<div class="devicetypes-list-wrapper row">
	<?php if ($devicetypes && (count($devicetypes) > 0)) { ?>
	<div class="cn-devicetypes-list col-xs-12">
		<div class="c-list-item q-desktop q-header hidden-xs hidden-sm row">
			<div class="p-name col-xs-2" title="Name">Name</div>
			<div class="p-devname col-xs-2" title="DevName">DevName</div>
			<div class="p-magaged col-xs-2" title="Managed">Managed</div>
			<div class="p-macaddress col-xs-2" title="MacAddress Pattern">MacAddressPattern</div>
			<div class="p-actions col-xs-4" title="Actions">Actions</div>
		</div>
		<?php foreach ($devicetypes as $dt) {?>
		<div class="c-list-item q-desktop hidden-xs hidden-sm row">
			<div class="p-name col-xs-2"><?php print $dt['Name'];?></div>
			<div class="p-devname col-xs-2"><?php print $dt['DevName'];?></div>
			<div class="p-magaged col-xs-2"><?php print ($dt['IsManageable']) ? t('Yes') : t('No'); ?></div>
			<div class="p-macaddress col-xs-2"><?php print $dt['MACAddressPattern']; ?></div>
			<div class="p-actions col-xs-4"><?php print theme('flowadmin_devicetypes_btn_panel', array('devicetypesID' => $dt['DeviceTypeID'])); ?></div>
		</div>
		<!-- Mobile view -->
		<div class="c-list-item q-mobile hidden-md hidden-lg row">
			<div class="cn-content col-xs-12">
				<div class="p-name row">
					<div class="cp-label col-xs-5">Name: </div>
					<div class="cp-value col-xs-7"><?php print $dt['Name'];?></div>
				</div>
				<div class="p-devname row">
					<div class="cp-label col-xs-5">Dev Name: </div>
					<div class="cp-value col-xs-7"><?php print $dt['DevName'];?></div>
				</div>
				<div class="p-magaged row">
					<div class="cp-label col-xs-5">Managed: </div>
					<div class="cp-value col-xs-7"><?php print ($dt['IsManageable']) ? t('Yes') : t('No'); ?></div>
				</div>
				<div class="p-macaddress row">
					<div class="cp-label col-xs-8 col-sm-5">MacAddress Pattern:</div>
					<div class="cp-value col-xs-4 col-sm-7"><?php print $dt['MACAddressPattern']; ?></div>
				</div>	
			</div>
			<div class="cn-btn-panel col-xs-12">
				<?php print theme('flowadmin_devicetypes_btn_panel', array('devicetypesID' => $dt['DeviceTypeID'])); ?>
			</div>
		</div>		
		
		<?php }?>
	</div>
	<div class="text-center">
	<?php
			$baseURL = base_path() . FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES;
			$pagerArgs = array('baseURL' => $baseURL, 'currentPage' => $pageNumber, 'pageCount' => $pageCount); 
			print theme('flowautho_pager', $pagerArgs);
	?>
	</div>
	
	<?php }else{?>
	<div class="cn-devicetypes-list col-xs-12">
		<?php print t('There are currently no device types in the system.'); ?>
	</div>
	<?php }?>
</div>

