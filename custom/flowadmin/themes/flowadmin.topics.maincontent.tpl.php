<div class="topics-list-wrapper row">
	<?php if ($topics && (count($topics) > 0)) { ?>
	<div class="cn-topics-list col-xs-12">
		<div class="c-list-item q-desktop q-header hidden-xs hidden-sm row">
			<div class="p-name col-xs-2" title="Name">Name</div>
			<div class="p-devicetopic col-xs-1" title="Device Topic">DeviceTopic</div>
			<div class="p-usertopic col-xs-1" title="User Topic">UserTopic</div>
			<div class="p-eventhistroy col-xs-2" title="Use Event History">EventHistory</div>
			<div class="p-maxage col-xs-2" title="Maximum Age(HH:MM:SS)">MaxAge(HH:MM:SS)</div>
			<div class="p-actions col-xs-4" title="Actions">Actions</div>
		</div>
		<?php foreach ($topics as $topic) {?>
		<div class="c-list-item q-desktop hidden-xs hidden-sm row">
			<div class="p-name col-xs-2"><?php print $topic['Name'];?></div>
			<div class="p-devicetopic col-xs-1"><?php print ($topic['IsDeviceTopic']) ? t('Yes') : t('No'); ?></div>
			<div class="p-usertopic col-xs-1"><?php print ($topic['IsUserTopic']) ? t('Yes') : t('No'); ?></div>
			<div class="p-eventhistroy col-xs-2"><?php print ($topic['UseEventHistory']) ? t('Yes') : t('No'); ?></div>
			<div class="p-maxage col-xs-2"><?php print $topic['MaxAge']; ?></div>
			<div class="p-actions col-xs-4"><?php print theme('flowadmin_topics_btn_panel', array('topic' => $topic)); ?></div>
		</div>
		<!-- Mobile view -->
		<div class="c-list-item q-mobile hidden-md hidden-lg row">
			<div class="cn-content col-xs-12">
				<div class="p-name row">
					<div class="cp-label col-xs-5">Name: </div>
					<div class="cp-value col-xs-7"><?php print $topic['Name'];?></div>
				</div>
				<div class="p-devicetopic row">
					<div class="cp-label col-xs-5">DeviceTopic: </div>
					<div class="cp-value col-xs-7"><?php print ($topic['IsDeviceTopic']) ? t('Yes') : t('No');?></div>
				</div>
				<div class="p-usertopic row">
					<div class="cp-label col-xs-5">UserTopic: </div>
					<div class="cp-value col-xs-7"><?php print ($topic['IsUserTopic']) ? t('Yes') : t('No'); ?></div>
				</div>
				<div class="p-eventhistroy row">
					<div class="cp-label col-xs-5">EventHistory:</div>
					<div class="cp-value col-xs-7"><?php print ($topic['UseEventHistory']) ? t('Yes') : t('No'); ?></div>
				</div>	
				<div class="p-maxage row">
					<div class="cp-label col-xs-5">MaxAge (HH:MM:SS):</div>
					<div class="cp-value col-xs-7"><?php print $topic['MaxAge']; ?></div>
				</div>					
			</div>
			<div class="cn-btn-panel col-xs-12">
				<?php print theme('flowadmin_topics_btn_panel', array('topic' => $topic)); ?>
			</div>
		</div>		
		
		<?php }?>
	</div>
	<div class="text-center">
	<?php
			$baseURL = base_path() . FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_TOPICS;
			$pagerArgs = array('baseURL' => $baseURL, 'currentPage' => $pageNumber, 'pageCount' => $pageCount); 
			print theme('flowautho_pager', $pagerArgs);
	?>
	</div>
	
	<?php }else{?>
	<div class="cn-topics-list col-xs-12">
		<?php print t('There are currently no FlowMessaging topics in the system.'); ?>
	</div>
	<?php }?>
</div>
