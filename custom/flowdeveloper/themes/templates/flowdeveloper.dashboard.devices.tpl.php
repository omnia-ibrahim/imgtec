<div class="c-device-list container-fluid">
	
	<?php   
	if($form['deviceCount']['#value'] > 1) {

		echo '<p>'. t('Monitor and manage your devices. You can register a new device, delete or edit the details of existing devices'). '</p>	
	<div class="c-device-managed c-select-all-checkbox row">
		<div class="c-device-icon col-xs-2 col-sm-1">
			<div class="form-type-checkbox form-item checkbox">
				<input class="form-checkbox checkbox-primary c-select-all-checkbox" type="checkbox" id="select-all-checkbox">
				<label for="select-all-checkbox" class="checkbox-shown c-ate-select-all-checkbox"></label>
			</div>
		</div>
		<span>SELECT ALL</span>
	</div>';
	}
	if ($form['deviceCount']['#value']) {
		for ($i = 0; $i < $form['deviceCount']['#value']; $i++) {
			$name = 'selected-device-'.$i;
			if ($form['devices'][$name]['#attributes']['ismanagable'][0] == TRUE) { ?>
				<div class="c-device-managed row">
					<div class="c-device-icon col-xs-2 col-sm-1"><?php print render($form['devices'][$name]); ?></div>
					<a class="c-device c-ate-device-list-managed-<?php print $i + 1; ?>" href="<?php print url(FDW_DASHBOARD . '/' . FDW_DEVICE . '/' . $form['devices'][$name]['#attributes']['deviceid'][0]); ?>" data-is-manageable="true" data-device-id="<?php print $form['devices'][$name]['#attributes']['deviceid'][0]; ?>">
						<div class="c-device-wrapper col-xs-9 col-lg-10">
							<div class="c-device-name c-ate-device-list-name-<?php print $i + 1; ?>"><?php print $form['devices'][$name]['#attributes']['devicename'][0]; ?></div>
							<div class="c-device-desc "><?php print $form['devices'][$name]['#attributes']['devicedesc'][0]; ?></div>
						</div>
						<div class="c-device-view-detail">
							<span class="c-device-list-status-info"><?php print t('Retrieving status...'); ?></span>
						</div>
					</a>

					<div class="c-device-list-status-icon c-device-default-status-icon"></div>
				</div>
			<?php }
			else { ?>
				<div class="c-device-unmanaged row">
					<div class="c-device-icon col-xs-2 col-sm-1"><?php print render($form['devices'][$name]); ?></div>
					<a class="c-device c-ate-device-list-unmanaged-<?php print $i + 1; ?>" href="<?php print url(FDW_DASHBOARD . '/' . FDW_DEVICE . '/' . $form['devices'][$name]['#attributes']['deviceid'][0]); ?>" data-is-manageable="false" data-device-id="<?php print $form['devices'][$name]['#attributes']['deviceid'][0]; ?>">
						<div class="c-device-wrapper col-xs-9 col-lg-10">
							<div class="c-device-name c-ate-device-list-name-<?php print $i + 1; ?>"><?php print $form['devices'][$name]['#attributes']['devicename'][0]; ?></div>
							<div class="c-device-desc "><?php print $form['devices'][$name]['#attributes']['devicedesc'][0]; ?></div>
						</div>
						<div class="c-device-view-detail">
							<span class="c-device-list-status-info"><?php print t('Unknown status'); ?></span>
						</div>
					</a>

					<div class="c-device-list-status-icon c-device-status-unknown">
					</div>
				</div>
			<?php }
		}
		
		//print render($form['submit']);
		print drupal_render_children($form);
	?>
	<button type="button" class="btn btn-default c-delete-device-btn c-ate-delete-device-list-btn"><span class="cp-icon"></span><?php print t('Delete'); ?></button>
	<?php 	
	}
	else
	{
		?>
		
		<div class="c-no-devices row">
			<div class="cp-teaser hidden-xs col-xs-12">
				<a href="<?php print url(FDW_DASHBOARD.'/'.FDW_DEVICES.'/'.FDW_DEVICES_REGISTER);?>"><img src="<?php print url(drupal_get_path('theme', 'highness').'/images/register-device-tip.png'); ?>" class="img-responsive center-block"/></a>
			</div>
			<div class="cp-teaser hidden-sm hidden-md hidden-lg col-xs-12">
				<a href="<?php print url(FDW_DASHBOARD.'/'.FDW_DEVICES.'/'.FDW_DEVICES_REGISTER);?>"><img src="<?php print url(drupal_get_path('theme', 'highness').'/images/register-device-tip-mobile.png'); ?>" class="img-responsive center-block"/></a>
			</div>
			<div class="cp-header center-text col-xs-12 c-ate-devices-no-devices">You have no registered devices.</div>
			<div class="cp-copy center-text col-xs-12">
				Register a device with your account to access device management and resource information using this dashboard.
			</div>
		</div>
		<?php
	}
	?>
</div>
