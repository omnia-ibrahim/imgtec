<?php 
		if($datastore['CanDelete'])
		{
			$deleteURL = base_path() . FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DATASTORES.'/'.$datastore['Name'].'/'.FLOWADMIN_DELETE;
?>
			<span class="c-control q-delete"><a href="<?php print $deleteURL; ?>"><?php print t('Delete'); ?></a></span>
<?php 	} ?>