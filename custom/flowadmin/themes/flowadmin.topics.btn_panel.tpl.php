<?php 
		if($topic['CanUpdate'] && $topic['CanDelete'])
		{
			$editURL = base_path() . FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_TOPICS.'/'.$topic['Name'].'/'.FLOWADMIN_EDIT;
			$deleteURL = base_path() . FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_TOPICS.'/'.$topic['Name'].'/'.FLOWADMIN_DELETE;
			//drupal_set_message('<pre>Topic:: '. $editURL.'</pre>');
?>
			<span class="c-control q-edit"><a href="<?php print $editURL; ?>"><?php print t('Edit'); ?></a></span>
			<span class="c-control q-delete"><a href="<?php print $deleteURL; ?>"><?php print t('Delete'); ?></a></span>
<?php 	} ?>		