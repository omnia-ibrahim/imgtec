<?php $baseURL = base_path() . FDW_DASHBOARD .'/'. FDW_LOGS .'/'. $logType;  ?>
<div class="c-log-entry-list container-fluid" 
	data-logtype="<?php print $logType; ?>" 
	data-currentpage="<?php print $currentPage; ?>"
	data-basepath="<?php print base_path() . FDW_DASHBOARD .'/'. FDW_LOGS; ?>">

	<div class="row"><?php print render($logTypeForm); ?></div>
	<?php
			$recordCount = 0;
			foreach ($logData as $key => $logEntries)
			{
				$recordCount += count($logEntries);
			}
			
			if ($recordCount > 0) 
			{
				$pageItemCounter = 1;
				foreach ($logData as $key => $logEntries) 
				{
					foreach ($logEntries as $logEntry)
					{
						if ($pageItemCounter <= $pageSize) 
						{
							$pageItemCounter++;
							$entryTime = flowdeveloper_utcTimeToDateTime($logEntry['EntryTime']);
	?>
							<div class="c-log-entry c-ate-log-entry row">
								<div class="row">
									<div class="cp-originator c-ate-log-originator col-xs-7 col-sm-8"><?php print $logEntry['Originator']; ?></div>
									<div class="cp-date c-ate-log-time  col-xs-5 col-sm-4"><?php print $entryTime; ?></div>
								</div>
								<div class="row">
									<div class="cp-content c-ate-log-content col-xs-12"><?php print $logEntry['Content']?></div>
								</div>			
							</div>
	<?php 
						}
					}
				}
			}
			else
			{
				print t('There are no log entries in your choosen log category.');				
			} 
		
	?>
	  
	
	<div class="text-center">
	<?php	print theme('flowdeveloper_pager', array('baseURL' => $baseURL, 'currentPage' => $currentPage, 'pageCount' => $pageCount)); ?>
	</div>
	
</div>