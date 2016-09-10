<?php

	$editURL = base_path() . FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES.'/'.$devicetypesID.'/'.FLOWADMIN_EDIT;
	$deleteURL = base_path() . FLOWADMIN_DASHBOARD.'/'.FLOWADMIN.'/'.FLOWADMIN_DEVICETYPES.'/'.$devicetypesID.'/'.FLOWADMIN_DELETE;
?>
	<span class="c-control"><a href="<?php print $editURL; ?>"><?php print t('Edit'); ?></a></span>
	<span class="c-control"><a href="<?php print $deleteURL; ?>"><?php print t('Delete'); ?></a></span>	