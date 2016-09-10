<div class="datastores-list-wrapper row">
	<?php if ($datastores && (count($datastores) > 0)) { ?>
	<div class="cn-datastores-list col-xs-12">
		<div class="c-list-item q-desktop q-header hidden-xs hidden-sm row">
			<div class="p-name col-xs-3" title="Name">Name</div>
			<div class="p-device-ds col-xs-3" title="Device Datastore">DeviceDatastore</div>
			<div class="p-user-ds col-xs-3" title="User Datastore">UserDatastore</div>
			<div class="p-actions col-xs-3" title="Actions">Actions</div>
		</div>
		<?php foreach ($datastores as $datastore) {?>
		<div class="c-list-item q-desktop hidden-xs hidden-sm row">
			<div class="p-name col-xs-3"><?php print $datastore['Name'];?></div>
			<div class="p-device-ds col-xs-3"><?php print ($datastore['IsDeviceDataStore']) ? t('Yes') : t('No'); ?></div>
			<div class="p-user-ds col-xs-3"><?php print ($datastore['IsUserDataStore']) ? t('Yes') : t('No'); ?></div>
			<div class="p-actions col-xs-3"><?php print theme('flowadmin_datastores_btn_panel', array('datastore' => $datastore)); ?></div>
		</div>
		<!-- Mobile view -->
		<div class="c-list-item q-mobile hidden-md hidden-lg row">
			<div class="cn-content col-xs-12">
				<div class="p-name row">
					<div class="cp-label col-xs-5">Name: </div>
					<div class="cp-value col-xs-7"><?php print $datastore['Name'];?></div>
				</div>
				<div class="p-devicetopic row">
					<div class="cp-label col-xs-5">DeviceDatastore: </div>
					<div class="cp-value col-xs-7"><?php print ($datastore['IsDeviceDataStore']) ? t('Yes') : t('No');?></div>
				</div>
				<div class="p-usertopic row">
					<div class="cp-label col-xs-5">UserDatastore: </div>
					<div class="cp-value col-xs-7"><?php print ($datastore['IsUserDataStore']) ? t('Yes') : t('No'); ?></div>
				</div>
			</div>
			<div class="cn-btn-panel col-xs-12">
				<?php print theme('flowadmin_datastores_btn_panel', array('datastore' => $datastore)); ?>
			</div>
		</div>		
		
		<?php }?>
	</div>
	<div class="text-center">
	<?php
			$baseURL = base_path() . FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DATASTORES;
			$pagerArgs = array('baseURL' => $baseURL, 'currentPage' => $pageNumber, 'pageCount' => $pageCount); 
			print theme('flowautho_pager', $pagerArgs);
	?>
	</div>
	
	<?php }else{?>
	<div class="cn-datastores-list col-xs-12">
		<?php print t('You have not yet created any Datastores.'); ?>
	</div>
	<?php }?>
</div>
