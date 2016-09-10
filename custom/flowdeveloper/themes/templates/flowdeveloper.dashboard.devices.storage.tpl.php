<div class="c-fdw-card q-status-item col-xs-12 col-md-5">
	<div class="cn-row-wrapper q-no-margin row">
		<div class="cp-header q-storage-item col-xs-12">
			<?php 
					$cardTitel = (isset($storageItem['Name'])) ?  $storageItem['Name'] .' ('.$storageItem['StorageType'].')' : $storageItem['StorageType'] ;
					print $cardTitel; 
			?>
		</div>
	</div>
	
	<?php if(isset($storageItem['FreeStorage']['Value']) && isset($storageItem['TotalStorage']['Value'])){ ?>
	
	<div class="cn-row-wrapper q-no-margin row">
		<div class="cp-icon q-storage col-xs-12">
			<?php	$usedAsPercentage = floor((($storageItem['UsedStorage']['Value']/$storageItem['TotalStorage']['Value']) * 100)); ?>
			<div class="cp-storage-map"><div class="cp-used pull-left" style="width: <?php print $usedAsPercentage; ?>%;"></div></div>
		</div>
	</div>
	<div class="cn-row-wrapper q-no-margin row">
		<div class="cp-description col-xs-12">
			<?php
					$desc = $storageItem['UsedStorage']['Value'].$storageItem['UsedStorage']['Unit']
						  . t(' used of ') .$storageItem['TotalStorage']['Value'].$storageItem['TotalStorage']['Unit'] ;
					print $desc; 
			?>
		</div>
	</div>
	<div class="cn-row-wrapper c-info-item q-storage-legend q-no-margin row">
		<div class="cp-icon q-used col-xs-1"><div class="cp-inner pull-left">&nbsp;</div></div>
		<div class="cp-label col-xs-4"><?php print t('Used'); ?></div>
		<div class="cp-value col-xs-6"><?php print $storageItem['UsedStorage']['Value'].$storageItem['UsedStorage']['Unit']; ?></div>
	</div>	
	<div class="cn-row-wrapper c-info-item q-storage-legend q-no-margin row">
		<div class="cp-icon q-free col-xs-1"><div class="cp-inner pull-left">&nbsp;</div></div>
		<div class="cp-label col-xs-4"><?php print t('Available'); ?></div>
		<div class="cp-value col-xs-6"><?php print $storageItem['FreeStorage']['Value'].$storageItem['FreeStorage']['Unit']; ?></div>
	</div>
	
	<?php } elseif (isset($storageItem['FreeStorage']['Value']) && (!isset($storageItem['TotalStorage']['Value'])) ){ ?>
	
	<div class="cn-row-wrapper c-info-item q-storage-legend q-no-margin row">
		<div class="cp-icon q-free col-xs-1"><div class="cp-inner pull-left">&nbsp;</div></div>
		<div class="cp-label col-xs-4"><?php print t('Available'); ?></div>
		<div class="cp-value col-xs-6"><?php print $storageItem['FreeStorage']['Value'].$storageItem['FreeStorage']['Unit']; ?></div>
	</div>	
	
	<?php } ?>	
</div>
