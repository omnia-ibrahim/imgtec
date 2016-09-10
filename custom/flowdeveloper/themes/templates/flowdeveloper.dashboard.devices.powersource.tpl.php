<?php	$psType = $powerSource['PowerSourceType'];

		if($powerSource['PowerSourceType'] == 'InternalBattery') {	?>
	
			<div class="c-fdw-card q-status-item col-xs-12 col-md-5">
				<div class="cn-row-wrapper q-no-margin row">
					<div class="cp-header q-powersource col-xs-12"><?php print $powerSource['PowerSourceType']; ?></div>
				</div>
				<div class="cn-row-wrapper q-no-margin row">
					<div class="cp-icon col-xs-12">
						<div class="c-power-battery"></div>
						<div class="c-power-battery-level-outer">
							<?php 	$blClass = '';
									if ($powerSource['Level'] <= 10) 
									{ 
										$blClass = "c-power-battery-verylow";
									}
									elseif ($powerSource['Level'] <= 20) 
									{
										$blClass = "c-power-battery-low";
									}; 
							?>
							<div class="c-power-battery-level <?php print $blClass; ?>" style="height: <?php print $powerSource['Level']; ?>%;"></div>
						</div>
					</div>
				</div>
				<div class="cn-row-wrapper q-no-margin row">
					<div class="cp-battery-status col-xs-12">
						<?php if ($powerSource['Status'] == "Charging") { ?>
							<div class="c-power-battery-charging"></div>
						<?php } ?>
					</div>
				</div>
				<div class="cn-row-wrapper q-no-margin row">
					<div class="cp-description col-xs-12">
						<?php print $powerSource['Status'] .' '. $powerSource['Level'] . '%'; ?>
					</div>
				</div>
				<div class="cn-row-wrapper c-info-item q-no-margin row">
					<div class="cp-label col-xs-8"><?php print t('Voltage (!unit)',array('!unit' => $powerSource['Voltage']['Unit'])); ?></div>
					<div class="cp-value col-xs-4"><?php print $powerSource['Voltage']['Value']; ?></div>
				</div>	
				<div class="cn-row-wrapper c-info-item q-no-margin row">
					<div class="cp-label col-xs-8"><?php print t('Current (!unit)',array('!unit' => $powerSource['Current']['Unit'])); ?></div>
					<div class="cp-value col-xs-4"><?php print $powerSource['Current']['Value']; ?></div>
				</div>
				<div class="cn-row-wrapper c-info-item q-no-margin row">
					<div class="cp-label col-xs-8"><?php print t('Power (!unit)',array('!unit' => $powerSource['Power']['Unit'])); ?></div>
					<div class="cp-value col-xs-4"><?php print $powerSource['Power']['Value']; ?></div>
				</div>				
			</div>
	

<?php 	} elseif (($psType == 'DC') || ($psType == 'AC') || ($psType == 'USB') || ($psType == 'PowerOverEthernet') || ($psType == 'Solar') || ($psType == 'ExternalBattery')) {
				  	
				  switch ($psType) 
				  {
				  	case 'ExternalBattery':
				  		$iconClass = ' c-exbattery ';
				  		break;
				  						  	
				  	case 'DC':
				  		$iconClass = ' c-acdc ';
				  		break;
				  		
				  	case 'AC':
				  		$iconClass = ' c-acdc ';
				  		break;		
				  		
				  	case 'USB':
				  		$iconClass = ' c-usb ';
				  		break;	
				  		
				  	case 'PowerOverEthernet':
				  		$iconClass = ' c-ethernet ';
				  		break;	

				  	case 'Solar':
				  		$iconClass = ' c-solar ';
				  		break;					  		
				  	
				  	default:
				  		$iconClass = ' c-acdc ';
				  		break;
				  	break;
				  }

				  //$statusClass = ($powerSource['Status'] == 'Connected') ? ' q-connected ' : ' q-disconnected ';
				  $statusClass = ' q-connected ';
?>

			<div class="c-fdw-card q-status-item col-xs-12 col-md-5">
				<div class="cn-row-wrapper q-no-margin row">
					<div class="cp-header q-powersource col-xs-12"><?php print $powerSource['PowerSourceType']; ?></div>
				</div>
				<div class="cn-row-wrapper q-no-margin row">
					<div class="cp-icon col-xs-12">
						<div class="<?php print $iconClass . ' '. $statusClass; ?>"></div>
					</div>
				</div>
				<div class="cn-row-wrapper q-no-margin row">
					<div class="cp-description col-xs-12"><?php print '&nbsp;'; //print $powerSource['Status']; ?></div>
				</div>
				<div class="cn-row-wrapper c-info-item q-no-margin row">
					<div class="cp-label col-xs-8"><?php print t('Voltage (!unit)',array('!unit' => $powerSource['Voltage']['Unit'])); ?></div>
					<div class="cp-value col-xs-4"><?php print $powerSource['Voltage']['Value']; ?></div>
				</div>	
				<div class="cn-row-wrapper c-info-item q-no-margin row">
					<div class="cp-label col-xs-8"><?php print t('Current (!unit)',array('!unit' => $powerSource['Current']['Unit'])); ?></div>
					<div class="cp-value col-xs-4"><?php print $powerSource['Current']['Value']; ?></div>
				</div>
				<div class="cn-row-wrapper c-info-item q-no-margin row">
					<div class="cp-label col-xs-8"><?php print t('Power (!unit)',array('!unit' => $powerSource['Power']['Unit'])); ?></div>
					<div class="cp-value col-xs-4"><?php print $powerSource['Power']['Value']; ?></div>
				</div>				
			</div>

<?php 	}  ?>

