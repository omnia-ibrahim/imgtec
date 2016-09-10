<?php 

function _flowdeveloper_process_events()
{
	$xmlPayload = file_get_contents('php://input');
	
	$xmlDoc = new DOMDocument();
	if ($xmlDoc->loadXML($xmlPayload)) 
	{
		//_flowautho_debug('[_flowdeveloper_process_events::] ReceivedXML: '. print_r($xmlDoc->saveXML(), true));
		$eventsManager = new FLDEventsManager();
		$responseCode = $eventsManager->processEvents($xmlDoc);
		
		header('HTTP/1.1 '.$responseCode);		
	}
	else
	{
		//_flowautho_debug('[_flowdeveloper_process_events::] Failed to load XML document: ');
		header('HTTP/1.1 '.IFLDEventResponseCodes::BAD_REQUEST);		
	}

	$response = '<?xml version="1.0" encoding="UTF-8"?>' ."\n"
			  . '<response>' ."\n"
			  . "\t" . '<data>Flowdeveoper website responding to FlowEvents</data>'
			  . '</response>' ."\n"
			  ;	
			  	
	echo $response;
}