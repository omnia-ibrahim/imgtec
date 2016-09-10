<div class="c-resource-instance row <?php print $extraClasses; ?>" data-iid="<?php print $instanceID; ?>" data-deviceid="<?php print $deviceID; ?>" data-roid="<?php print $objectID; ?>">
	<?php if($instanceCount > 1 ){?>
		<div class="c-header-wrapper col-xs-12">
			<div class="c-header row">
				<div class="cp-name col-xs-9 col-md-11 ">Instance <?php print $instanceID; ?></div>
				<div class="cp-resource-meta col-xs-3 col-md-1">
					<span class="cp-icon"></span>
				</div>
			</div>
		</div>
	<?php }?>
	<div class="cp-details col-xs-12">
		<img src="<?php print url(drupal_get_path('theme', 'highness').'/images/ic-reload-preloader.svg'); ?>" />
	</div>
</div>