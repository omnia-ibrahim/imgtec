<?php if($isLicenseeAdmin) {?>
		<div class="c-db-left-col col-xs-12 col-md-6 ">
			<div class="c-reg-devices c-component">
				<div class="c-header">Registered Devices</div>
				<div class="c-content">
					<div class="c-primary"><?php print $primaryMetric; ?></div>				
					<div class="c-secondary"><?php print $secondaryMetric; ?></div>
				</div>
			</div>
		</div>	
<?php } else { ?>
		<div class="c-db-left-col col-xs-12 col-md-6 ">
			<div class="c-reg-devices c-component">
				<div class="c-header">Registered Devices</div>
				<div class="c-content">
					<div class="c-primary q-not-la"><?php print $primaryMetric; ?></div>				
				</div>
			</div>
		</div>
<?php } ?>