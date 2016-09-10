
/**
 * The main function is wrappered in a closure and passed JQuery version 1.9 which should be forwarded
 * to all javascript objects involved in the dashboard.
 */
;(function($){
	
	//console.log('JQuery Version - Closure: ' + $.fn.jquery);
	$(document).ready(function(){
		
		/**
		 * Manages all the javascript objects that represent the different dashboard UI elements
		 */
		var DashboardManager = {
			
			init: function(){
				
				var dashboardPage = $('.c-dashboard-canvas');
				if(dashboardPage.length > 0)
				{
					var ladmin = Drupal.settings.flowdevuser.ladmin;
					RegisteredDevices.init();
					ConnectedDevices.init();
					DeviceBandwith.init();
					if (ladmin == '1') 
					{
						FirmwareVersions.init();
					} 					
					//console.log(ladmin);
				}
			},
			
			get_metrics: function(ajaxURL, ajaxData){
				
				var ajaxResponse = null;
				$.ajax({ 
					type: "POST", 
					url: ajaxURL, 
					async: false,
					dataType: 'json', 
					data: ajaxData,
					success: function(jsonData){
						ajaxResponse = jsonData;	
					},
					error: function(e, jqxhr, ajaxOptions, thrownError){
					}
				});
				
				return ajaxResponse;
			},
			
			init_close_drilldown_trigger: function(drillDownObject, hideInstead){
				
				$(drillDownObject)
				.find('.c-close-btn-wrapper > .c-close-btn')
				.click(function(e){
					Flowdeveloper.unblockUI({onUnblock: function(element, options){
						
						if (hideInstead == true) 
						{
							DashboardManager.reset_drilldown_options(drillDownObject);
							drillDownObject.appendTo('.jstemplate');
						} 
						else 
						{
							drillDownObject.remove();
						}
						
					}});
				});
			},
			
			show_drilldown: function(drillDown, width, height, overlayBGColor){
				
				Flowdeveloper.blockUIForm(drillDown, width, height, overlayBGColor);
			},
			
			validate_date_range: function(startDate, endDate)
			{
				var sd = Flowdeveloper.formatDateFromDatePicker(startDate);
				var ed = Flowdeveloper.formatDateFromDatePicker(endDate);
				var sdParts = sd.split('-');
				var edParts = ed.split('-');
				var sdY = Number(sdParts[0]); // start date Year
				var sdM = Number(sdParts[1]); // start date Month
				var sdD = Number(sdParts[2]); // start date Day
				var edY = Number(edParts[0]); // end date Year
				var edM = Number(edParts[1]); // end date Month
				var edD = Number(edParts[2]); // end date Day
				var validRange = false;
				
				if(sdY < edY)
				{
					validRange = true;
				}
				else if(sdY == edY)
				{
					if (sdM < edM) 
					{
						validRange = true;
					}
					else if (sdM == edM) 
					{
						if(sdD <= edD)
						{
							validRange = true;
						}							
					}					
				}
				
				return validRange;
			},
			
			reset_drilldown_options: function(drillDownObject)
			{
				var optionsF = drillDownObject.find('#flowdeveloper-form-drilldown-options');
				var origStartDate = optionsF.find('input[name="orig_start_date"]').val();
				var origEndDate = optionsF.find('input[name="orig_end_date"]').val();
				
				optionsF.find('input[name="start_date"]').val(origStartDate);
				optionsF.find('input[name="end_date"]').val(origEndDate);
				optionsF.find('input[type="checkbox"]').each(function(){
					if($(this).is(':checked'))
					{
						$(this).removeAttr('checked');
					}
				});				
			}
		};
		
		/**
		 * Manages the device types multi-select ui component
		 */
		var DashBoardMultiSelect = {
				
			get_multiselect_widget: function(deviceTypes, opFormID, drillDown, summariseStatus){
				
				var multiSelect = Flowdeveloper.cloneJSTemplate('#drilldown-multiselect-template');
				var optionsPanel = multiSelect.find('.c-options-panel');
				
				var dtCount = deviceTypes.length;
	        	for ( var i = 0; i < dtCount; i++) 
	        	{
	        		//var record = deviceTypes[i];
	        		//var deviceType = record.devicetype;
	        		var deviceType = deviceTypes[i];
	        		var option = Flowdeveloper.cloneJSTemplate('#generic-checkbox-template');
	        		var oname = 'devicetype[' + deviceType + ']';
	        		var ovalue = deviceType;
	        		var checkbox = option.find('input[type="checkbox"]');
	        		checkbox.attr('name', oname).attr('value', ovalue);
	        		var statusFormat = 0;
	        		/**
	        		 * bind click event to refresh status bar
	        		 */
	        		if (summariseStatus) 
	        		{
						var statusFormat = 1;
					} 
	        		
	        		checkbox.unbind('click');
	        		checkbox.bind('click', {_formID:opFormID, _statusFormat: statusFormat}, DashBoardMultiSelect.refresh_statusbar_handler);
	        		
	        		option.find('.c-label').html(deviceType);
        			optionsPanel.append(option);
				}
	        	
	        	/**
	        	 * Close the Options panel if the user clicks any where on the
	        	 * drilldown window.
	        	 */
	        	drillDown.unbind('click');
	        	drillDown.bind('click', {_op: optionsPanel}, DashBoardMultiSelect.hide_options_panel_handler);	        	
	        	
	        	return multiSelect;
			},
			
			multiselect_handler: function(e){
				
				var _formID = e.data._formID;
				var form = $('#'+_formID);
				var statusBar =  form.find('.c-status-panel .c-status');
				var optionsPanel = form.find('.c-options-panel');
				var checkboxCollection = form.find();
				
				
				//optionsPanel.show();
				if (optionsPanel.css('display') == 'block') 
				{
					DashBoardMultiSelect.hide_options_panel(optionsPanel);
				}
				else
				{
					DashBoardMultiSelect.show_options_panel(optionsPanel);
				}
			},
			
			show_options_panel: function(optionsPanel){
				
				optionsPanel.css({
					display: 'block',
					position: 'absolute',
			        top: '173px',
			        left: '531px',
			        'z-index':'1000'});
			},
			
			hide_options_panel: function(optionsPanel){
				optionsPanel.css({display:'none'});
			},
			
			get_selected_checkboxes: function(form){
				
				var selectedOptions = [];
				form.find('input[type="checkbox"]').each(function(){
					if($(this).is(':checked'))
					{
						selectedOptions.push($(this).val());
					}
				});
				
				return selectedOptions;
			},
			
			refresh_statusbar_handler: function(e){
				
				var _formID = e.data._formID;
				var _statusFormat = e.data._statusFormat;
				var form = $('#'+_formID);
				var statusBar =  form.find('.c-status-panel .c-status');
				var selectedOptions = DashBoardMultiSelect.get_selected_checkboxes(form);
				var maxDisplayLength = Number(30);
				var newStatus = selectedOptions.join();
				
				if (_statusFormat == '1') 
				{
					if(newStatus.length > maxDisplayLength) 
					{
						statusBar.html(selectedOptions.length + ' device types selected');
					} 
					else 
					{
						statusBar.html(newStatus);	
					}					
				} 
				else 
				{
					statusBar.html(selectedOptions.length + ' selected');
				}

			},
			
			hide_options_panel_handler: function(e){
				
				var target = $(e.target);
				var optionsPanel = e.data._op;
				//console.log('[hide_options_panel_handler::]');
				//console.log(target);
        		if( (!target.hasClass('c-control-btn')) &&
        			(!target.hasClass('c-status')) &&
        			(!target.hasClass('c-drilldown-update-btn')) && 
        			(target.attr('type') != 'checkbox') )
        		{
	        		//optionsPanel.hide();
        			DashBoardMultiSelect.hide_options_panel(optionsPanel);
        		}
			}
						
		};
		
		/**
		 * This object will manage RegisteredDevices and DeviceTypes UI components
		 */
		var RegisteredDevices = {
			
			init: function(){
				
				var ajaxURL = Flowdeveloper.get_base_path() + 'dashboard/ajax/registered-devices-bytype';
				var ajaxData = {};
				var jsonData = DashboardManager.get_metrics(ajaxURL, ajaxData);
				RegisteredDevices.render_devices_by_type_summary(jsonData);
			},
			
 			render_devices_by_type_summary: function(jsonData){
				
				if(jsonData != undefined)
				{
					//console.log('[RegisteredDevices::render_devices_by_type_summary] jsonData:: ');
					//console.log(jsonData);
					if (jsonData.error == '0') 
					{
						var chartData = jsonData.metrics;
						var data = [];
				        var tdata = new google.visualization.DataTable();
				        tdata.addColumn('string', 'Device Type');
				        tdata.addColumn('number', 'Device Count');
				        
						jQuery.each(chartData, function(i, val){
							var aname = val.name;
							data.push([ aname.toString(), Number(val.dcount)]);
						});
						tdata.addRows(data);
						
				        // Set chart options
				        var options = {
				        			'width':'100%', 
				        			'height':'100%', 
				        			'backgroundColor':'#f6f6f6',
				        			is3D: true,
				        	        chartArea: {
				        	            left: "3%",
				        	            top: "5%",
				        	            height: "80%",
				        	            width: "94%"
				        	        }
				       };				
						
				        // Instantiate and draw our chart, passing in some options.
				        var chart = new google.visualization.PieChart(document.getElementById('reg-devices-bytype-chart'));
				        chart.draw(tdata, options);
						$(window).on('debouncedresize', function( event ) {
							chart.draw(tdata, options);
						});
					}
					else
					{
						var cdchart = $('#reg-devices-bytype-chart');
						cdchart.html('No data available at this time').css({
									'width':'100%', 
									'height':'100%', 
									'text-align':'center',
									'padding-top':'100px'
						});
					}						
				}
				
			}
		};
		
		/**
		 * This object with manage connected devices UI components
		 */
		var ConnectedDevices = {
				
			init: function(){
				
				var ajaxURL = Flowdeveloper.get_base_path() + 'dashboard/ajax/connected-devices';
				var ajaxData = {};
				var jsonData = DashboardManager.get_metrics(ajaxURL, ajaxData);	
				ConnectedDevices.render_connected_devices_summary(jsonData, 'connected-devices-chart', 1012, 350);
				ConnectedDevices.init_drilldown_trigger(jsonData);
			},

			render_connected_devices_summary: function(jsonData, chartContainer, chartWidth, chartHeight){
				
				if(jsonData != undefined)
				{
					if (jsonData.error == '0') 
					{
						var chartData = jsonData.metrics;
						var data = [];
				        var tdata = new google.visualization.DataTable();   
				        tdata.addColumn('string', 'Month Day');
				        tdata.addColumn('number', 'Device Count');
				        
						jQuery.each(chartData, function(i, val){
							var aname = val.date;
							data.push([ aname.toString(), Number(val.connected)]);
						});
						tdata.addRows(data);
						
				        // Set chart options
				        var options = { 'width':'100%', 
				        				'height':'100%', 
				        				'backgroundColor':'#f6f6f6', 
				        				colors:['green'],
				        				hAxis: {slantedText:true, slantedTextAngle:90},
				        				legend: { position: 'top' },
			        				    chartArea: {
					        	            left: "4%",
					        	            top: "5%",
					        	            height: "70%",
					        	            width: "94%"
					        	        }
				        				};				
				        // Instantiate and draw our chart, passing in some options.
				        var chart = new google.visualization.ColumnChart(document.getElementById(chartContainer));
				        chart.draw(tdata, options);
						$(window).on('debouncedresize', function( event ) {
							chart.draw(tdata, options);
						});
					}
					else
					{
						var cdchart = $('#'+chartContainer);
						cdchart.html('No data available at this time').css({
									'width':'100%', 
									'height':'100%', 
									'text-align':'center',
									'padding-top':'150px'
						});
					}
				}				
			},
			
			init_drilldown_trigger: function(initialJasonData){
				
				//console.log('[ConnectedDevices::] init_drilldown_trigger:: InitialJasonData');
				//console.log(initialJasonData);
				var ddbtn = $('.c-connected-devices.c-component .c-drill-down-trigger.q-connected-devices');
				if(ddbtn.length > 0)
				{
					//var ddheader = ddbtn.attr('data-title');
					ddbtn.click(function(e){
						
						var discriminatorClass = 'q-devices-connected';
						var containerID = 'devices-connected-dd-chart';
						var drillDown = $('#period-dashboard-drilldown-popup-template').appendTo('body');
						
						drillDown.find('.c-header').html($(this).attr('data-title'));
						drillDown.addClass(discriminatorClass);
						drillDown.find('.c-page-content .c-drilldown-chart').attr('id', containerID);
						
						var deviceTypes = initialJasonData.devicetypes;
						if (deviceTypes.length > 0) 
						{
							var opFormID = 'flowdeveloper-form-drilldown-options-period';
							var opForm = $('#' + opFormID);
							
							var multiSelect = DashBoardMultiSelect.get_multiselect_widget(deviceTypes, opFormID, drillDown,0 );
							var optionsPanel = multiSelect.find('.c-options-panel');
							/**
				        	 * Bind a click event on the control to show the checkboxes
				        	 */
				        	//var selectControl = multiSelect.find('.c-status-panel .c-control-btn');
				        	var selectControl = multiSelect.find('.c-status-panel .c-status, .c-status-panel .c-control-btn');
				        	selectControl.unbind('click');
				        	selectControl.bind('click', {_formID:opFormID}, DashBoardMultiSelect.multiselect_handler);
				        	
				        	opForm.find('.c-dd-multiselect').remove();
				        	multiSelect.insertAfter(opForm.find('.c-period'));
				        	$('#edit-date-intervals-month').attr('checked', 'checked');

						}
						else
						{
							opForm = 'No data available!';
						}			
						
						var updateTrigger = opForm.find('.c-drilldown-update-btn');
						updateTrigger.unbind('click');
						updateTrigger.bind('click', 
										   {	_drilldown:drillDown, 
												_chartContainerID:containerID,
												_op: optionsPanel,
												_formID:opFormID
										   }, 
										   ConnectedDevices.update_drilldown_handler);						
						
						DashboardManager.init_close_drilldown_trigger(drillDown, true);
						DashboardManager.show_drilldown(drillDown, 960, 615, '#000000');
						ConnectedDevices.render_connected_devices_summary(initialJasonData, containerID, 855, 380);
						
					});
				}
			},
			
			update_drilldown_handler: function(e){
				
				drillDown = e.data._drilldown;
				_chartContainerID = e.data._chartContainerID;
				var form = drillDown.find('#flowdeveloper-form-drilldown-options-period');
				var selectedPeriod = form.find('input:radio[name="date_intervals"]:checked').val();
				var deviceTypes = [];
				
				form.find('input[type="checkbox"]').each(function(){
					if($(this).is(':checked'))
					{
						deviceTypes.push($(this).val());
					}
				});
				
				var ajaxURL = Flowdeveloper.get_base_path() + 'dashboard/ajax/drill-down/connected-devices';
				var ajaxData = {_period:selectedPeriod, _devicetypes: deviceTypes.join()};
				var jsonData = DashboardManager.get_metrics(ajaxURL, ajaxData);	
				//console.log('[update_drilldown_handler::] jsonData::');
				//console.log(jsonData);
				
				if(jsonData != undefined)
				{
					if (jsonData.error == '0') 
					{
						var chartData = jsonData.metrics.metricsdata;
						var deviceTypes = jsonData.metrics.devicetypes;
						var data = [];
				        var tdata = new google.visualization.DataTable();
			        	tdata.addColumn('string', 'Month day');						        
				        if ((deviceTypes.length > 0) && (deviceTypes != 'none')) 
				        {
				        	var dtCount = deviceTypes.length;
				        	for ( var i = 0; i < dtCount; i++) 
				        	{
				        		tdata.addColumn('number', deviceTypes[i]);	
							}
				        	
					        var recordCount = chartData.length;
					        for ( var i = 0; i < recordCount; i++) 
					        {
					        	var record = chartData[i];
								var tempDate = record.date;
								var dateParts  = tempDate.split('_');
								var formatedDate = dateParts[0] + ' ' + dateParts[1];
								var rowData = record.data;
								var columnCount = rowData.length;
								
								var row = [formatedDate.toString()];
								for ( var k = 0; k < columnCount; k++) 
								{
									var columnData = rowData[k];
									row.push(Number(columnData.connected));
								}
								data.push(row);
							}						        	
						}
				        else
				        {
					        tdata.addColumn('number', 'Device Count');
					        var recordCount = chartData.length;
					        for ( var i = 0; i < recordCount; i++) 
					        {
					        	var record = chartData[i];
					        	var date = record.date;
					        	var row = [date.toString(), Number(record.connected)];
					        	data.push(row);
					        }
				        }
				        
						tdata.addRows(data);
						var options = { 'width':'855px', 
										'height':'380px', 
										'backgroundColor':'#f6f6f6',
										curveType: 'function',
										hAxis: {slantedText:true, slantedTextAngle:90 },
										legend: { position: 'top' },
										chartArea:{width:"80%",height:"60%"}};							
						
				        // Instantiate and draw our chart, passing in some options.
						if (selectedPeriod == 'month') 
						{
					        var chart = new google.visualization.ColumnChart(document.getElementById('devices-connected-dd-chart'));
					        chart.draw(tdata, options);											
						}
						else
						{
					        var chart = new google.visualization.LineChart(document.getElementById('devices-connected-dd-chart'));
					        chart.draw(tdata, options);											
						}
						
					}
				}					
			}
			
			

			
		};
		
		var FirmwareVersions = {
				
			init: function(){
				
				var ajaxURL = Flowdeveloper.get_base_path() + 'dashboard/ajax/devices-by-firmware-versions';
				var ajaxData = {};
				var jsonData = DashboardManager.get_metrics(ajaxURL, ajaxData);	
				FirmwareVersions.render_devices_by_firmware_versions_summary(jsonData);
				FirmwareVersions.init_drilldown_trigger();
			},	
			
			render_devices_by_firmware_versions_summary: function(jsonData){
				
				if(jsonData != undefined)
				{
					if (jsonData.error == '0') 
					{
						var chartData = jsonData.metrics.fbydevicetype;
						var firmwareCount = jsonData.metrics.fwcount;
						$('.c-dashboard-canvas .c-firmware-versions-count.c-component .c-content').html(firmwareCount);
						var data = [];
				        var tdata = new google.visualization.DataTable();
				        tdata.addColumn('string', 'Firmware Version');
				        tdata.addColumn('number', 'Device Count');
				        
						jQuery.each(chartData, function(i, val){
							var aname = val.firmware;
							//data.push([ aname.toString(), Number(val.dcount)]);
							data.push([ aname.toString(), Number(val.devicecount)]);
						});
						tdata.addRows(data);
						
						 // Set chart options
				        var options = {
				        				'width':'100%', 
				        				'height':'100%', 
				        				'backgroundColor':'#f6f6f6', 
				        				pieHole: 0.3,
			        				    chartArea: {
					        	            left: "3%",
					        	            top: "5%",
					        	            height: "80%",
					        	            width: "94%"
					        	        }
				        				};				
						
				        // Instantiate and draw our chart, passing in some options.
				        var chart = new google.visualization.PieChart(document.getElementById('devices-by-firmware-version-chart'));
				        chart.draw(tdata, options);
						$(window).on('debouncedresize', function( event ) {
							chart.draw(tdata, options);
						});				        
					}
					else
					{
						var cdchart = $('#devices-by-firmware-version-chart');
						cdchart.html('No data available at this time').css({
									'width':'100%', 
									'height':'100%', 
									'text-align':'center',
									'padding-top':'100px'
						});
						
						$('.c-dashboard-canvas .c-firmware-versions-count.c-component .c-content')
						.html('No data available at this time')
						.css({
								'font-size':'14px',
								'font-weight':'normal',
								'color': '#7a7a7a',
								'padding-top':'100px'
						});
						
					}					
				}				
			},
			
			init_drilldown_trigger: function(){
				
				var ddbtn = $('.c-devices-by-firmware-version.c-component .c-drill-down-trigger.q-firmware-versions');
				if(ddbtn.length > 0)
				{
					ddbtn.click(function(e){
						
						var ajaxURL = Flowdeveloper.get_base_path() + 'dashboard/ajax/drill-down/firmware-versions';
						var ajaxData = {};
						var jsonData = DashboardManager.get_metrics(ajaxURL, ajaxData);
						
						var discriminatorClass = 'q-firmware-versions';	
						var containerID = 'firmware-versions-dd-chart';
						var drillDown = $('#generic-dashboard-drilldown-popup-template').appendTo('body');
						
						drillDown.find('.c-header').html($(this).attr('data-title'));
						drillDown.addClass(discriminatorClass);
						drillDown.find('.c-page-content .c-drilldown-chart').attr('id', containerID);
						drillDown.find('form').remove();
						
						if(jsonData != undefined)
						{
							if (jsonData.error == '0') 
							{
								//console.log('[FirmwareVersions::init_drilldown_trigger] Click');
								//console.log(jsonData);
								
								var deviceTypes = jsonData.metrics;
								if (deviceTypes.length > 0) 
								{
									var opFormID = 'firmware-versions-options';
									var opForm = Flowdeveloper.cloneJSTemplate('#generic-form-template');
									var multiSelect = Flowdeveloper.cloneJSTemplate('#drilldown-multiselect-template');
									var optionsPanel = multiSelect.find('.c-options-panel');
									opForm.attr('id', opFormID);
									
						        	var dtCount = deviceTypes.length;
						        	for ( var i = 0; i < dtCount; i++) 
						        	{
						        		var record = deviceTypes[i];
						        		var deviceType = record.devicetype;
						        		var option = Flowdeveloper.cloneJSTemplate('#generic-checkbox-template');
						        		var oname = 'devicetype[' + deviceType + ']';
						        		var ovalue = deviceType;
						        		var checkbox = option.find('input[type="checkbox"]');
						        		checkbox.attr('name', oname).attr('value', ovalue);
						        		/**
						        		 * bind click event to refresh status bar
						        		 */
						        		checkbox.unbind('click');
						        		checkbox.bind('click', {_formID:opFormID},FirmwareVersions.refresh_statusbar_handler);
						        		
						        		option.find('.c-label').html(deviceType);
					        			optionsPanel.append(option);
									}
						        	
						        	/**
						        	 * Bind a click event on the control to show the checkboxes
						        	 */
						        	var selectControl = multiSelect.find('.c-status-panel .c-status, .c-status-panel .c-control-btn');
						        	selectControl.unbind('click');
						        	selectControl.bind('click', {_formID:opFormID}, FirmwareVersions.multiselect_handler);
						        	
						        	opForm.append(multiSelect);
						        	
						        	/**
						        	 * Close the Options panel if the user clicks any where on the
						        	 * drilldown window.
						        	 */
						        	drillDown.unbind('click');
						        	drillDown.bind('click', {_op: optionsPanel}, FirmwareVersions.hide_options_panel_handler);
								}
								else
								{
									opForm = 'No data available!';
								}
								
								var updateTrigger = opForm.find('.c-drilldown-update-btn');
								updateTrigger.unbind('click');
								updateTrigger.bind('click', 
										{_formID:opFormID, _dstore:jsonData, _op: optionsPanel, _containerID:containerID}, 
										FirmwareVersions.update_drilldown_handler);
								
								drillDown.find('.c-page-content .c-control-panel').append(opForm);														
								DashboardManager.init_close_drilldown_trigger(drillDown, true);
								DashboardManager.show_drilldown(drillDown, 960, 615, '#000000');
							}
						}
						
					});
				}
			},
			

			multiselect_handler: function(e){
				
				var _formID = e.data._formID;
				var form = $('#'+_formID);
				var statusBar =  form.find('.c-status-panel .c-status');
				var optionsPanel = form.find('.c-options-panel');
				var checkboxCollection = form.find();
				
				//optionsPanel.show();
				if (optionsPanel.css('display') == 'block') 
				{
					FirmwareVersions.hide_options_panel(optionsPanel);
				}
				else
				{
					FirmwareVersions.show_options_panel(optionsPanel);
				}
				
			},
			
			show_options_panel: function(optionsPanel){
				optionsPanel.css({
					display: 'block',
					position: 'absolute',
			        top: '175px',
			        left: '62px' });
			},
			
			hide_options_panel: function(optionsPanel){
				optionsPanel.css({display:'none'});
			},
			
			get_selected_checkboxes: function(form){
				
				var selectedOptions = [];
				form.find('input[type="checkbox"]').each(function(){
					if($(this).is(':checked'))
					{
						selectedOptions.push($(this).val());
					}
				});
				
				return selectedOptions;
			},
			
			refresh_statusbar_handler: function(e){
				
				var _formID = e.data._formID;
				var form = $('#'+_formID);
				var statusBar =  form.find('.c-status-panel .c-status');
				var selectedOptions = FirmwareVersions.get_selected_checkboxes(form);
				var maxDisplayLength = Number(30);
				var newStatus = selectedOptions.join();
				if(newStatus.length > maxDisplayLength) 
				{
					statusBar.html(selectedOptions.length + ' device types selected');
				} 
				else 
				{
					statusBar.html(newStatus);	
				}
			},
			
			hide_options_panel_handler: function(e){
				
				var target = $(e.target);
				var optionsPanel = e.data._op;
        		if( (!target.hasClass('c-control-btn')) && 
        			(!target.hasClass('c-status')) &&
        			(!target.hasClass('c-drilldown-update-btn')) && 
        			(target.attr('type') != 'checkbox') )
        		{
	        		//optionsPanel.hide();
	        		FirmwareVersions.hide_options_panel(optionsPanel);
        		}
			},
			
			render_drilldown_item: function(jsonData){
				
				var themedItem = 'There are no firmware updates for this device type';
				var header = jsonData.devicetype;
				var fwVersions = jsonData.fwversions;
				var fwCount = fwVersions.length;
				
				if(fwCount > Number(0))
				{
					themedItem = Flowdeveloper.cloneJSTemplate('#firmware-breakdown-template');
					themedItem.find('.c-header').html(header);
					var tableBody = themedItem.find('.c-content table tbody');
					
					for ( var i = 0; i < fwCount; i++) 
					{
						var row = fwVersions[i];
						//var tableRow = Flowdeveloper.cloneJSTemplate('#firmware-breakdown-row-template');
						tableRow = $('#firmware-breakdown-row-template').find('tr').clone();	
						tableRow.find('td.q-fwversion').html(row.fwversion);
						tableRow.find('td.q-device-count').html(row.dcount);
						tableRow.find('td.q-percentage').html(row.percentage);
						tableBody.append(tableRow);
					}
				}
				
				return themedItem;
			},
			
			update_drilldown_handler: function(e){

				var _formID = e.data._formID;
				var form = $('#'+_formID);				
				var _dataStore = e.data._dstore;
				var optionsPanel = e.data._op;
				var targetContainer = $('#' + e.data._containerID);
				var selectedOptions = FirmwareVersions.get_selected_checkboxes(form);
				
				//optionsPanel.hide();
				FirmwareVersions.hide_options_panel(optionsPanel);
				targetContainer.empty();
				if (selectedOptions.length > 0) 
				{
					var data = _dataStore.metrics;
					var dtCount = data.length;
					for ( var i = 0; i < dtCount; i++) 
					{
						dtRecord = data[i];
						if(selectedOptions.indexOf(dtRecord.devicetype) >= Number(0)) 
						{
							themedRecord = FirmwareVersions.render_drilldown_item(dtRecord);
							targetContainer.append(themedRecord);
						}
					}
				}
				
				//console.log('[FirmwareVersions::update_drilldown_handler] DataStore:: ');
				//console.log(_dataStore);
				//console.log(selectedOptions);
			}
			
		};
		
		var DeviceBandwith = {

				init: function(){
					
					var ajaxURL = Flowdeveloper.get_base_path() + 'dashboard/ajax/devices-bandwidth';
					var ajaxData = {};
					var jsonData = DashboardManager.get_metrics(ajaxURL, ajaxData);	
					DeviceBandwith.render_devices_bandwidth_summary(jsonData, 'devices-bandwidth-chart', 1012, 350);
					DeviceBandwith.init_drilldown_trigger(jsonData);
				},	
				
				render_devices_bandwidth_summary: function(jsonData, chartContainer, chartWidth, chartHeight){
					
					if(jsonData != undefined)
					{
						if (jsonData.error == '0') 
						{
							var chartData = jsonData.metrics;
							var data = [];
					        var tdata = new google.visualization.DataTable();
					        tdata.addColumn('string', 'Month day');
					        tdata.addColumn('number', 'Bandwith(KB)');
					        
							jQuery.each(chartData, function(i, val){
								var aname = val.date;
								data.push([ aname.toString(), Number(val.bandwidth)]);
							});
							tdata.addRows(data);
							
							 // Set chart options
							var options = { 'width':'100%', 
											'height':'100%', 
											'backgroundColor':'#f6f6f6',
											curveType: 'function',
											hAxis: {slantedText:true, slantedTextAngle:90 },
											legend: { position: 'top' },
				        				    chartArea: {
						        	            left: "5%",
						        	            top: "5%",
						        	            height: "70%",
						        	            width: "90%"
						        	        }		
							};							
							
					        // Instantiate and draw our chart, passing in some options.
					        var chart = new google.visualization.LineChart(document.getElementById(chartContainer));
					        chart.draw(tdata, options);	
							$(window).on('debouncedresize', function( event ) {
								chart.draw(tdata, options);
							});						        
						}
						else
						{
							var cdchart = $('#'+chartContainer);
							cdchart.html('No data available at this time').css({
										'width':'100%', 
										'height': '100%', 
										'text-align':'center',
										'padding-top':'150px'
							});
						}						
					}				
				},
				
				init_drilldown_trigger: function(initialJasonData){
					
					var ddbtn = $('.c-devices-bandwidth.c-component .c-drill-down-trigger.q-connected-devices-bandwidth');
					if(ddbtn.length > 0)
					{
						ddbtn.click(function(e){
							
							var discriminatorClass = 'q-devices-bandwidth';
							var containerID = 'devices-bandwidth-dd-chart';
							var drillDown = $('#daterange-dashboard-drilldown-popup-template').appendTo('body');
							
							drillDown.find('.c-header').html($(this).attr('data-title'));
							drillDown.addClass(discriminatorClass);
							drillDown.find('.c-page-content .c-drilldown-chart').attr('id', containerID);
							
							var deviceTypes = initialJasonData.devicetypes;
							if (deviceTypes.length > 0) 
							{
								var opFormID = 'flowdeveloper-form-drilldown-options';
								var opForm = $('#' + opFormID);
								
								var multiSelect = DashBoardMultiSelect.get_multiselect_widget(deviceTypes, opFormID, drillDown,0 );
								var optionsPanel = multiSelect.find('.c-options-panel');
								
								/**
					        	 * Bind a click event on the control to show the checkboxes
					        	 */
					        	var selectControl = multiSelect.find('.c-status-panel .c-status, .c-status-panel .c-control-btn');
					        	selectControl.unbind('click');
					        	selectControl.bind('click', {_formID:opFormID}, DashBoardMultiSelect.multiselect_handler);
					        	
					        	opForm.find('.c-dd-multiselect').remove();
					        	multiSelect.insertAfter(opForm.find('.c-period'));

							}
							else
							{
								opForm = 'No data available!';
							}
							
							var updateTrigger = opForm.find('.c-drilldown-update-btn');
							updateTrigger.unbind('click');
							updateTrigger.bind('click', 
											   {	_drilldown:drillDown, 
													_chartContainerID:containerID,
													_op: optionsPanel,
													_formID:opFormID
											   }, 
											   DeviceBandwith.update_drilldown_handler);
							
							//drillDown.find('.c-page-content .c-control-panel').append(opForm);
							DashboardManager.init_close_drilldown_trigger(drillDown, true);
							DashboardManager.show_drilldown(drillDown, 960, 615, '#000000');
							DeviceBandwith.render_devices_bandwidth_summary(initialJasonData, containerID, 855, 380);	
							
							Flowdeveloper.setupDatePicker('edit-start-date', false);
							Flowdeveloper.setupDatePicker('edit-end-date', true);							
						});
 
					}
				},
				
				update_drilldown_handler: function(e){
					
					drillDown = e.data._drilldown;
					_chartContainerID = e.data._chartContainerID;
					var form = drillDown.find('#flowdeveloper-form-drilldown-options');
					var startDate = form.find('input[name="start_date"]').val();
					var endDate = form.find('input[name="end_date"]').val();
					var deviceTypes = [];
					
					form.find('input[type="checkbox"]').each(function(){
						if($(this).is(':checked'))
						{
							deviceTypes.push($(this).val());
						}
					});
					
					/**
					 * Validate date range
					 */
					//console.log('[update_drilldown_handler::]StartDate: ' + startDate);
					//console.log('[update_drilldown_handler::]EndDate: ' + endDate);
					//console.log('[update_drilldown_handler::]SelectedDeviceTypes:');
					//console.log(deviceTypes);
					
					form.find('input[name="start_date"]').removeClass('error');
					form.find('input[name="end_date"]').removeClass('error');
					
					if (DashboardManager.validate_date_range(startDate, endDate)) 
					{
						formattedSD = Flowdeveloper.formatDateFromDatePicker(startDate);
						formattedED = Flowdeveloper.formatDateFromDatePicker(endDate);
						var ajaxURL = Flowdeveloper.get_base_path() + 'dashboard/ajax/drill-down/devices-bandwidth';
						var ajaxData = {_startdate: formattedSD,  _enddate: formattedED, _devicetypes: deviceTypes.join()};
						var jsonData = DashboardManager.get_metrics(ajaxURL, ajaxData);	
						//console.log('[update_drilldown_handler::] jsonData::');
						//console.log(jsonData);
						
						if(jsonData != undefined)
						{
							if (jsonData.error == '0') 
							{
								var chartData = jsonData.metrics.metricsdata;
								var deviceTypes = jsonData.metrics.devicetypes;
								var data = [];
						        var tdata = new google.visualization.DataTable();
					        	tdata.addColumn('string', 'Month day');						        
						        if ((deviceTypes.length > 0) && (deviceTypes != 'none')) 
						        {
						        	var dtCount = deviceTypes.length;
						        	for ( var i = 0; i < dtCount; i++) 
						        	{
						        		tdata.addColumn('number', deviceTypes[i]);	
									}
						        	
							        var recordCount = chartData.length;
							        for ( var i = 0; i < recordCount; i++) 
							        {
							        	var record = chartData[i];
										var tempDate = record.date;
										var dateParts  = tempDate.split('_');
										var formatedDate = dateParts[0] + ' ' + dateParts[1];
										var rowData = record.data;
										var columnCount = rowData.length;
										
										var row = [formatedDate.toString()];
										for ( var k = 0; k < columnCount; k++) 
										{
											var columnData = rowData[k];
											row.push(Number(columnData.bandwidth));
										}
										data.push(row);
									}						        	
								}
						        else
						        {
							        tdata.addColumn('number', 'Bandwith(KB)');
							        var recordCount = chartData.length;
							        for ( var i = 0; i < recordCount; i++) 
							        {
							        	var record = chartData[i];
							        	var date = record.date;
							        	var row = [date.toString(), record.bandwidth];
							        	data.push(row);
							        }
						        }
						        
								tdata.addRows(data);
								var options = { 'width':'855px', 
												'height':'380px', 
												'backgroundColor':'#f6f6f6',
												curveType: 'function',
												hAxis: {slantedText:true, slantedTextAngle:90 },
												legend: { position: 'top' },
												chartArea:{width:"80%",height:"60%"}};							
								
						        // Instantiate and draw our chart, passing in some options.
								$('devices-bandwidth-dd-chart > div').remove();
						        var chart = new google.visualization.LineChart(document.getElementById('devices-bandwidth-dd-chart'));
						        chart.draw(tdata, options);											
							}
						}
					}
					else
					{
						form.find('input[name="start_date"]').addClass('error');
						form.find('input[name="end_date"]').addClass('error');
					}
				}
				
		};
		
		/**
		 * Initialize dashboard
		 */
		DashboardManager.init();

		
		
	});
	
})(jQuery, window);






