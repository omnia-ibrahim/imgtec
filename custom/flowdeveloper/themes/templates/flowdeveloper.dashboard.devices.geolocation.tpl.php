<div class="c-fdw-card q-status-item q-geo-location col-xs-12 col-md-5">
	<div class="cn-row-wrapper q-no-margin row">
		<div class="cp-header q-geo-location col-xs-12">
			<?php print t('Geo Location'); ?>
			<div class="cp-time"><?php print flowdeveloper_utcTimeToDateTime($locationData['Timestamp']); ?></div>
		</div>
	</div>
	<div class="cn-row-wrapper q-no-margin row">
		<div id="device-geo-location-map" class="q-storage col-xs-12" data-lat="<?php print $locationData['Latitude']; ?>" data-long="<?php print $locationData['Longitude']; ?>">
		</div>
	</div>
	<div class="cn-row-wrapper q-no-margin row">
		<div id="device-geo-location-address" class="cp-description col-xs-12">
		</div>
	</div>	
	<div class="cn-row-wrapper c-info-item q-no-margin row">
		<div class="cp-label col-xs-8"><?php print t('Latitude(N/S)'); ?></div>
		<div class="cp-value col-xs-4"><?php print $locationData['Latitude']; ?></div>
	</div>
	<div class="cn-row-wrapper c-info-item q-no-margin row">
		<div class="cp-label col-xs-8"><?php print t('Longitude(E/W)'); ?></div>
		<div class="cp-value col-xs-4"><?php print $locationData['Longitude']; ?></div>
	</div>
	<div class="cn-row-wrapper c-info-item q-no-margin row">
		<div class="cp-label col-xs-8"><?php print t('Altitude(Meter)'); ?></div>
		<div class="cp-value col-xs-4"><?php print $locationData['Altitude']; ?></div>
	</div>	
</div>