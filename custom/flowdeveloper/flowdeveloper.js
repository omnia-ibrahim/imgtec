/** 
 * Module related JS functionality: flowdeveloper
 * Constants, namespaces and related functions.
 * Created by murat.ereksel on 06/08/2015.
 */

/**
 * Define constants
 */

var FDW_AJAX = "ajax", FDW_USER = "user",
    FDW_DEVICE = 'device', FDW_RESOURCES = 'resources',
    FCAP_ENDPOINT = FDW_AJAX + '/' +FDW_USER + '/retrieve-fcap',
    RETRIEVE_DEVICE_STATUS_ENDPOINT = FDW_AJAX + '/'  + FDW_DEVICE + '/retrieve-status',
    RETRIEVE_DEVICE_INFO_ENDPOINT = FDW_AJAX + '/'  + FDW_DEVICE + '/retrieve-info',
    UPDATE_DEVICE_INFO_ENDPOINT = FDW_AJAX + '/' + FDW_DEVICE + '/update-info',
	FDW_DEVICES = 'devices', FDW_REG_GUIDE = 'reg-guide';


/**
 * Define namespaces
 */
/**
var Flowdeveloper = {},
    fdw_user = {}, fdw_sip = {}, fdw_devices= {},
    PasswordIssuesForm ={}, UserProfileForm = {}, DeleteDeviceForm = {},
    RegisterForm = {}, LoginForm = {}, LogViewer = {},
    DeviceDetails = {}, DeviceResources = {}, FlowAuthoModule = {}, AppBuilder = {}, DeviceRegistration = {};
**/

var fdw_user = {}, fdw_sip = {}, fdw_devices= {},
	PasswordIssuesForm ={}, UserProfileForm = {}, DeleteDeviceForm = {},
	RegisterForm = {}, LoginForm = {}, LogViewer = {},
	DeviceDetails = {}, DeviceResources = {}, AppBuilder = {}, DeviceRegistration = {};

/**
 * Global vars
 */
var is_page_active = false;

/**
 * Public and private functions for the namespaces defined above.
 * For the ones that you need to call publicly, use the format namespace.methodName = function(){...} or simply use "this" instead of the namespace.
 * For internal use (within the closure) just write the function name(){..} on its own and call it privately.
 *
 */

/**
(function (){
    this.setupDatePicker = function (elID, restrictFutureDate) {
        var options = {dateFormat: "M dd, yy", minDate: -370, maxDate: 0};
        $('#' + elID).datepicker(options);
    };
    this.formatDateFromDatePicker = function (dpDate) {

        return $.datepicker.formatDate("yy-mm-dd", $.datepicker.parseDate('M dd, yy', dpDate));
    };
    this.cloneJSTemplate = function (templateSelector) {
        return $(templateSelector).clone().removeAttr('id');
    };
    this.blockUIfunction = function () {

        var preloader = Flowdeveloper.cloneJSTemplate('#ajax-preloader-template');
        $.blockUI({
            message: preloader,
            centerX: true,
            centerY: true,
            overlayCSS: {backgroundColor: '#ffffff', opacity: 0.5},
            css: {
                top: ($(window).height() - 48) / 2 + 'px',
                left: ($(window).width() - 48) / 2 + 'px',
                width: '48px',
                height: '48px',
                border: 'none',
                color: '#7A7A7A',
                backgroundColor: 'transparent',
                cursor: 'default'
            }
        });
    };
    this.unblockUI = function (options) {
        $.unblockUI(options);
    };
    this.blockUIForm = function (form, fwidth, fheight, overlayBGColor) {

        if ((overlayBGColor == undefined) || (overlayBGColor.length < Number(1))) {
            overlayBGColor = '#ffffff';
        }
        $.blockUI({
            message: form,
            centerX: false,
            centerY: true,
            overlayCSS: {backgroundColor: overlayBGColor, opacity: 0.5},
            css: {
                top: ($(window).height() - fheight) / 2 + 'px',
                left: ($(window).width() - fwidth) / 2 + 'px',
                width: fwidth + 'px',
                height: fheight + 'px',
                border: 'none',
                color: '#7A7A7A',
                backgroundColor: 'transparent',
                cursor: 'default'
            }
        });
    };
    this.get_base_path = function () {
        return Drupal.settings.basePath;
    };
    this.getCookie = function(cookieName){
        var name = cookieName + "=";
        var ca = document.cookie.split(';');
        for(var i=0; i<ca.length; i++) {
            var c = ca[i];
            while (c.charAt(0)==' ') c = c.substring(1);
            if (c.indexOf(name) == 0) return c.substring(name.length,c.length);
        }
        return "";
    };
    this.setCookie = function(cookieName, cookieValue, expiry_in_days){
        var d = new Date();
        var expires = "";
        if(expiry_in_days) {
            d.setTime(d.getTime() + (expiry_in_days*24*60*60*1000));
            expires = "expires="+d.toUTCString();
        }
        document.cookie = cookieName + "=" + cookieValue + "; " + expires + "; path=/";
    };
    this.removeCookie = function(cookieName){
        document.cookie = cookieName + "=" + "" + "; " + "-1";
        //this.setCookie(cookieName,"","-1");
    };
    this.getURIParameter = function (theParameter) {
        var params = window.location.search.substr(1).split('&');

        for (var i = 0; i < params.length; i++) {
            var p=params[i].split('=');
            if (p[0] == theParameter) {
                return decodeURIComponent(p[1]);
            }
        }
        return false;
    };
    this.globalNotify = function(notification, force_global){
        if(Notification.permission !== 'granted'){
            Notification.requestPermission();
        }
        if(notification.icon == undefined || notification.icon == ""){
            notification.icon = ""; //TODO: add default notify icon here.
        }

        if(force_global == true){
            n = new Notification( notification.title, {
                body: notification.body ,
                icon : notification.icon
            });
        }
        else {
            if(!is_page_active){
                n = new Notification( notification.title, {
                    body: notification.body ,
                    icon : notification.icon
                });
            }
        }

    }

}.call(Flowdeveloper)); 
**/
/** Main Flowdeveloper module JS functions **/
(function (){
    this.get_fcap = function (){
        var code = 0;
        $.ajax({
            type: 'GET',
            async: false,
            url: Drupal.settings.basePath + FCAP_ENDPOINT,
            error: function() {
                //return an error code: The theme should know what to make of it.
                code = data;
            },
            success: function(data) {
                code = data;
            }
        });

        return code;
    }
    
    /**
    this.init_controls = function (){

        $ = jQuery;
        var userProfileForm = $('#user-profile-form');
        if(userProfileForm.length > 0)
        {
        	fdw_user.init_user_profile_form(userProfileForm);
        }
    }
    **/
    
}.call(fdw_user)); /** User Profile related functions **/
(function (){

    var $devices_info = {},
        $sip_entity_count = 0,
        device_guid_uri_map = {},
        ws_connected = false;

    this.init_controls = function(){
        if(window.location.href.indexOf(Drupal.settings.flowSip.FDW_MESSAGE_VIEWER) > -1){
            if (!SIP.WebRTC.isSupported()) {
                alert("Your browser doesn't support WebRTC thus you can't use the message viewer. Please switch to a modern browser.");
                window.location.href = Drupal.settings.basePath + '/dashboard';
            }
            else{
                if(window.location.href.indexOf(Drupal.settings.flowSip.FDW_MESSAGE_VIEWER_V2) > -1){
                    this.init();
                }
                else {
                    this.pub_sub_init();
                }
            }
        }
    };
    this.init = function (){
        $ = jQuery;


        var $devices_sip_settings = JSON.parse(Drupal.settings.flowSip.user_devices_sip_settings),
            $SIPDomain = JSON.parse(Drupal.settings.flowSip.user_sip_settings).SIPDomain,
            $i = 0;



        //Append user settings to device settings.
        $devices_sip_settings.push(JSON.parse(Drupal.settings.flowSip.user_sip_settings));

        for($i=0;$i<$devices_sip_settings.length;$i++){

            device_guid_uri_map[$devices_sip_settings[$i].URI] = $devices_sip_settings[$i].GUID;

            // Create client
            var client = createUA(
                $devices_sip_settings[$i].URI
                ,$devices_sip_settings[$i].UserName
                ,$devices_sip_settings[$i].PasswordHash
                ,$devices_sip_settings[$i].GUID
            );

            client.start();

            $sip_entity_count = $sip_entity_count + 1;

            client.on('connected', function () {
                var date = get_message_timestamp();

                if(ws_connected) return;
                $('#log').prepend('<div class="notice notice-info"> ' +
                    '<strong>Successful ~' +
                    '</strong> Connected to the websocket! Please wait for SIP registration ...  <span class="message-date-time pull-right text-muted">' + date + '</span></div>');

                ws_connected = true;
            });
            client.on('registered', function (message) {

                var $entity = "User";
                /**
                 * Let's cache the device details for this session
                 */
                if(is_user_id(message.to.uri.user)) {
                    //Get user info and stuff.
                }
                else{
                    var $deviceGUID = device_guid_uri_map["sip:" + message.to.uri.aor];
                    cacheDeviceDetails($deviceGUID);
                    var $deviceInfo = getCachedDeviceDetails($deviceGUID);
                    $entity = $deviceInfo.DeviceName;
                }

                //$('#man-devices').append("<option id='" + $deviceInfo.DeviceId + "'>" + $deviceInfo.DeviceName + "</option>")

                var date = get_message_timestamp();
                $('#log').prepend('<div class="notice notice-info"> ' +
                    '<strong>Successful ~ ' +
                    '</strong> Registered on the SIP (message) server as <b>' + $entity + '</b><br/>Now you can send and receive messages.<span class="message-date-time pull-right text-muted">' + date + '</span></div>');

                //Add into filters too.
                //If it's not already added.
                var $mv_toolbox = $('#message-viewer-tool-box');
                var $already_exists = false;

                $mv_toolbox.children('button').each(function() {
                    if($(this).attr("data-entity-id") == message.to.uri.user) $already_exists = true;
                });

                if(!$already_exists) $mv_toolbox.append('<button data-entity-id="' + message.to.uri.user + '" class="c-message-filter-button btn btn-primary btn-md">' + $entity + '</button> &nbsp;');

            });
            client.on('registrationFailed', function (cause) {
                var date = get_message_timestamp();

                $('#log').prepend('<div class="notice notice-danger"> ' +
                    '<strong>Error ~ ' +
                    '</strong>Registration has failed - ' + cause + ' <span class="pull-right text-muted">' + date + '</span></div>');

            });
            client.on('message', function (message) {

                var date = get_message_timestamp();
                var $entity = "User",
                    $deviceGUID = '',
                    $deviceInfo = '';

                if(is_user_id(message.request.to.uri.user)){ //if(1 || )
                    //get user info and stuff
                }
                else{
                    $deviceGUID = device_guid_uri_map["sip:" + message.request.to.uri.user + "@" + $SIPDomain];
                    //$deviceInfo = getCachedDeviceDetails($deviceGUID);
                    //$entity = $deviceInfo.DeviceName;
                }

                var $msg = "";
                if(message.body.indexOf("<") > -1 && message.body.indexOf(">") > -1){
                    var xml = $.parseXML(message.body);
                    var xmlDoc = $(xml);
                    $msg = formatXml(xmlDoc[0].documentElement.outerHTML);
                }
                else{
                    $msg = message.body;
                }


                $('#log').prepend('<div data-entity-id="' + message.request.to.uri.user + '" class="notice notice-info">' +
                    'Message - <b>' + $entity  + '</b>' +
                    '<pre> ' +
                    $msg +
                    '</pre>' +
                    '<span class="pull-right text-muted">' + date + '</span><br/></div>');

            });

        }


        window.onunload = function () {
            unregisterClient(client);
        };

        $('.sendmessage').on("click", function(){

            $receiver = $('#message-receiver-field').val();
            $message = $('#message-field').val();

            sendMessage(client, $receiver, $message);

        });
        $('#clear-log').on("click", function(){
            $('#log').empty();
        });

        //Init filtering too ..
        this.filterMessages();
    };
    this.pub_sub_init = function(){

        //Retrieve user SIP login credentials
        $user_credentials = JSON.parse(Drupal.settings.flowSip.user_sip_settings);
        $user_guid = Drupal.settings.flowSip.user_guid;

        // Create client
        var client = createUA(
            $user_credentials.URI
            ,$user_credentials.UserName
            ,$user_credentials.PasswordHash
            //,displayname
        );

        client.start();


        $ = jQuery;
        /**
         * Handles, subscribe || unsubscribe
         */
        $('.c-topic-subscribe').on('click', function(){

            //Get variables
            var subs_list = $('.subscription-list'),
                sip_log = $('#sip-log'),
                subs_notice_line = $('.subscription-notice-line'),
                data_topic_name = $(this).attr("data-topic-name");


            /**
             * SUBSCRIBE
             * @SIP SUBSCRIBE
             */
            if($(this).attr("data-checked") == "false") {

                //Set it to on
                $(this).attr("data-checked", "true");

                //If device || user
                var x_topic,
                    is_user_topic;
                if($(this).attr("data-is-device-topic") == "true"){
                    x_topic = $(this).attr("data-client-id") + ":" + $(this).attr("data-topic-name");
                    is_user_topic = "false";
                }
                else{
                    x_topic = $user_guid + ":" + $(this).attr("data-topic-name");
                    is_user_topic = "true";
                }

                //Create subscription
                var subscription = client.subscribe( //(target, event, options, is_user_topic x_topic, x_instanceid)
                    $user_credentials.URI,
                    "flow-event",
                    null,
                    is_user_topic,
                    x_topic,
                    "");

                //If we are good then let them know and start listening
                if(subscription.state == "active" || true){ //TODO check this.
                    if(subs_list.children().length == 0){
                        //First remove the subsline if it is there and has the empty state message in it.
                        if(subs_notice_line.attr("data-is-empty") == "true"){
                            subs_notice_line.remove();
                        }
                        sip_log.append('<div class="notice notice-info subscription-notice-line">Subscribed to <span class="subscription-list"><span id="topic_' + data_topic_name +'"> <b>'+ $(this).attr("data-topic-name") +'</b> </span></span> successfully.</div>');
                    } else{
                        subs_list.append(' <span id="topic_' + $(this).attr("data-topic-name") + '"><b>, '+ data_topic_name +'</b></span>');
                    }

                    subscription.on('notify', function(request) {
                        if(request.request.body != ""){
                            $('#sip-log').append('<div class="notice notice-info">' + request.request.body + '</div>');
                        }
                    });
                }
            }

            /**
             * UNSUBSCRIBE
             * @SIP SUBSCRIBE with 0 expiry
             */

            else{

                //Set it to off
                $(this).attr("data-checked", "false");

                //Remove it from the subscription list
                if(subs_list.children().length == 1){ //or < 2
                    subs_notice_line.html("Currently not subscribed to anything.").attr("data-is-empty", "true");
                }
                else{
                    $('#topic_' + data_topic_name).remove();
                }
            }

        });

    };

    this.filterMessages = function(){
        $(document).on("click","body .c-message-filter-button", function() {

            var $btns = $('.c-message-filter-button');

            if ($(this).attr("data-entity-id") == 'all') {
                $('#log > div').fadeIn(450);
            } else {
                var entity_id = $(this).attr("data-entity-id");
                var $el = $('div[data-entity-id="' + entity_id + '"]').fadeIn(450);

                $('#log > div').not($el).hide();
            }
            $btns.removeClass('active');
            $(this).addClass('active');
        });
    };

    function createUA(callerURI, userName, password, displayName) {

        var configuration = {
            traceSip: true,
            uri: callerURI,
            authorizationUser: userName,
            password: password,
            wsServers: [Drupal.settings.flowSip.websocket_sever],
            registrarServer: Drupal.settings.flowSip.registrar_server,
            displayName: displayName,
            userAgentString: Drupal.settings.flowSip.user_agent_string
        };

        var userAgent = new SIP.UA(configuration);
        return userAgent;
    }
    function sendMessage(userAgent,target, msg) {
        // Only send a message if the message is non-empty
        if (msg != '') {
            userAgent.message(target, msg);
        }
    }
    function registerForMessage(userAgent, event){
        userAgent.on(event, function (msg) {
            console.log(msg.body);
        });
    }
    function unregisterClient(client){
        var options = {
            'all': true
        };
        //client.unregister(options);
        client.stop();
    }
    function enableMessaging(){

        $('#register-client').hide();
        $('#send-message-form').show();

        $('#message-sender-field').val($('#sip-uri').val());
        /*$('#message-field').removeAttr("disabled");
         $('#message-send-button').removeAttr("disabled");*/
    }
    function get_message_timestamp(){
        var time = new Date().getTime();
        var date_full = new Date(time);
        var stripped_date = date_full.toString().substr(0, date_full.toString().indexOf("GMT"));
        return stripped_date;
    }
    function getDeviceInfo(deviceID) {
        var $deviceInfo = Array();
        $.ajax({
            type: 'GET',
            async: false,
            url: Drupal.settings.basePath + RETRIEVE_DEVICE_INFO_ENDPOINT + "/" + deviceID,
            error: function() {},
            success: function($data) {
                $deviceInfo = JSON.parse($data);
            }
        });

        return $deviceInfo;
    }
    function cacheDeviceDetails($deviceID){

        var device_details = getDeviceInfo($deviceID);
        var a = [$deviceID];

        for(var i=0;i<a.length;i++) {
            $devices_info[a[i]] = device_details;
        }

    }
    function getCachedDeviceDetails($deviceID){
        for(var key in $devices_info) {
            if(key == $deviceID){
                return $devices_info[key];
            }
        }
    }
    function formatXml(xml) {
        var formatted = '';
        var reg = /(>)(<)(\/*)/g;
        xml = xml.replace(reg, '$1\r\n$2$3');
        var pad = 0;
        jQuery.each(xml.split('\r\n'), function(index, node) {
            var indent = 0;
            if (node.match( /.+<\/\w[^>]*>$/ )) {
                indent = 0;
            } else if (node.match( /^<\/\w/ )) {
                if (pad != 0) {
                    pad -= 1;
                }
            } else if (node.match( /^<\w[^>]*[^\/]>.*$/ )) {
                indent = 1;
            } else {
                indent = 0;
            }

            var padding = '';
            for (var i = 0; i < pad; i++) {
                padding += '  ';
            }

            node = node.replace("<", "&#60;").replace(">", "&#62;").replace("/", "&#47;");
            formatted += padding + node + '\r\n';
            pad += indent;
        });

        return formatted;
    }
    function is_user_id(txt){

        var re1='(U)';	// Single Character U
        var re2='(-)';	// Single Character -
        var re3='(\\d+)';	// Integer Number

        var p = new RegExp(re1+re2+re3,["i"]);
        var m = p.exec(txt);


        if (m != null)
        {
            var c1=m[1];
            var c2=m[2];
            var int1=m[3];

            if(c1.length > 0 && c2.length > 0 && int1.length > 0){
                return true;
            }
            else { return false; }

        }
        else{
            return false;
        }
    }

}.call(fdw_sip)); /** SIP & Messaging - PubSub related functions **/

/** Form related closures **/
(function (){
    this.init_controls = function(){
        var form_register = $('#user-register-form--2');
        var ATEDataKey = 'ate-class-name';
        	
        if (form_register.length > 0)
        {
            $.validator.addMethod( "username1", function( value, element ) {
            	//$(element).data(ATEDataKey, 'c-ate-error-registration-validation-msg-name');
                return this.optional( element ) || /^[a-z0-9]+.*/i.test( value );
            }, Drupal.settings.flowdevmsg.errorusername1 );
            $.validator.addMethod( "username2", function( value, element ) {
            	//$(element).data(ATEDataKey, 'c-ate-error-registration-validation-msg-name');
                return this.optional( element ) || /^[a-z0-9]+[a-z0-9-_.]+$/i.test( value );
            }, Drupal.settings.flowdevmsg.errorusername2 );
            $.validator.addMethod( "email1", function( value, element ) {
            	//$(element).data(ATEDataKey, 'c-ate-error-registration-validation-msg-mail');
                return this.optional( element ) || /[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?/.test( value );
            }, Drupal.settings.flowdevmsg.erroremail1 );
            $.validator.addMethod( "password1", function( value, element ) {
            	//$(element).data(ATEDataKey, 'c-ate-error-registration-validation-msg-pass');
                return this.optional( element ) || /\d/.test( value );
            }, Drupal.settings.flowdevmsg.errorpassword1 );
            form_register.validate({
                rules: {
                    name: {
                        required: true,
                        username1: true,
                        username2: true,
                        minlength: 5
                    },
                    pass: {
                        required: true,
                        password1: true,
                        minlength: 6
                    },
                    mail: {
                        required: true,
                        email1: true
                    }
                },
                focusCleanup: true,
                errorClass: "error",
                errorPlacement: function( label, element ) {
                	var ateClass = '';
                	var elName = element.attr('name');
                	if(elName == 'name')
                	{
                		ateClass = 'c-ate-error-registration-validation-msg-name';
                	}
                	else if (elName == 'mail') 
                	{
                		ateClass = 'c-ate-error-registration-validation-msg-mail';
					}
                	else if (elName == 'pass') 
                	{
                		ateClass = 'c-ate-error-registration-validation-msg-pass';
					}                         	

                	label.addClass(ateClass);
                	
                    label.addClass("c-error-msg-label");
                    //label.addClass("c-ate-error-validation-msg-" + element.attr("name"));
                    
                    
                    if( element.attr( "type" ) === "checkbox" || element.attr( "type" ) === "radio" ) {
                        element.parent().append( label );
                    }
                    else {
                        label.insertAfter( element );
                    }
                },
                invalidHandler: function() {
                    $(".c-ate-is-loaded").addClass('c-ate-loaded');
                },
                messages: {
                    name: {
                        required: Drupal.settings.flowdevmsg.errorrequired,
                        minlength: Drupal.settings.flowdevmsg.errorminlength
                    },
                    pass: {
                        required: Drupal.settings.flowdevmsg.errorrequired,
                        minlength: Drupal.settings.flowdevmsg.errorminlength
                    },
                    mail: {
                        required: Drupal.settings.flowdevmsg.errorrequired
                    }
                }
            });
        }
    }
}.call(RegisterForm));
(function (){
    this.init_controls = function(){
        var form_login = $('#user-login--2');

        if (form_login.length > 0)
        {
            form_login.validate({
                rules: {
                    name: {
                        required: true
                    },
                    pass: {
                        required: true
                    }
                },
                focusCleanup: true,
                errorClass: "error",
                errorPlacement: function( label, element ) {
                    label.addClass("c-error-msg-label");
                    var elName = element.attr("name");
                    var ateClass = '';
                    if(elName == 'name')
                    {
                    	ateClass = 'c-ate-error-login-validation-msg-name';
                    }
                    else if (elName == 'pass') 
                    {
                    	ateClass = 'c-ate-error-login-validation-msg-pass';
					}
                    //label.addClass("c-ate-error-validation-msg-" + element.attr("name"));
                    label.addClass(ateClass);
                    
                    if( element.attr( "type" ) === "checkbox" || element.attr( "type" ) === "radio" ) {
                        element.parent().append( label );
                    }
                    else {
                        label.insertAfter( element );
                    }
                },
                invalidHandler: function() {
                    $(".c-ate-is-loaded").addClass('c-ate-loaded');
                },
                messages: {
                    name: {
                        required: Drupal.settings.flowdevmsg.erroremail2
                    },
                    pass: {
                        required: Drupal.settings.flowdevmsg.errorpassword2
                    }
                }
            });
        }
    }
}.call(LoginForm));
(function (){
    this.init_controls = function(){

        var form = jQuery('#user-pass--2');
        if (form.length > 0)
        {
            var passwordTrigger = form.find('.c-resend-passord-btn');
            var activationEmail = form.find('.c-resend-act-email-btn');
            passwordTrigger.bind('click', {_form: form}, PasswordIssuesForm.send_new_password_handler);
            activationEmail.bind('click', {_form: form}, PasswordIssuesForm.send_acc_activation_email_handler);
        }
    };

    this.send_new_password_handler = function (e) {

        var form = e.data._form;
        form.find('input[name="desired_op"]').val('send-new-password');
        form.submit();
    };

    this.send_acc_activation_email_handler = function (e) {

        var form = e.data._form;
        form.find('input[name="desired_op"]').val('send-acc-activation-email');
        form.submit();
    }
}.call(PasswordIssuesForm));
(function (){
    this.init_controls = function(){

        $ = jQuery;
        var upForm = $('#user-profile-form');
        if (upForm.length > 0)
        {
        	UserProfileForm.init_user_profile_form(upForm);
            var saveBtn = upForm.find('#edit-submit');
            saveBtn.bind('click', {_form: upForm}, UserProfileForm.save_profile);
        }
    };
    
    this.init_user_profile_form = function(userProfileForm){
    	
    	var $ = jQuery;
    	var passwordStrengthContainer = Flowdeveloper.cloneJSTemplate('#password-strength-container-template');
    	var passwordContainer = $('#user-profile-form .form-type-password-confirm .form-item-pass-pass1');
    	passwordStrengthContainer.insertAfter(passwordContainer.find('.password-strength'));
    	passwordContainer.find().appendTo(passwordStrengthContainer);
    	
    	var leftColumn = passwordStrengthContainer.find('.cn-confirm-password');
    	var rightColumn = passwordStrengthContainer.find('.cn-password-strength');
    	passwordContainer.find('.password-strength').appendTo(rightColumn);
    	passwordContainer.find('label[for="edit-pass-pass1"], #edit-pass-pass1').appendTo(leftColumn); 
    	
    	//console.log(leftColumn);
    	//console.log(rightColumn);
    	
        $.validator.addMethod( "username1", function( value, element ) {
            return this.optional( element ) || /^[a-z0-9]+.*/i.test( value );
        }, Drupal.settings.flowdevmsg.errorusername1 );
        $.validator.addMethod( "username2", function( value, element ) {
            return this.optional( element ) || /^[a-z0-9]+[a-z0-9-_.]+$/i.test( value );
        }, Drupal.settings.flowdevmsg.errorusername2 );  
        $.validator.addMethod( "email1", function( value, element ) {
            return this.optional( element ) || /[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?/.test( value );
        }, Drupal.settings.flowdevmsg.erroremail1 );
		$.validator.addMethod( "password1", function( value, element ) {
		    return this.optional( element ) || /\d/.test( value );
		}, Drupal.settings.flowdevmsg.errorpassword1 ); 
		
        userProfileForm.validate({
        
        	rules:{
                name: {
                    required: true,
                    username1: true,
                    username2: true,
                    minlength: 5
                },
                
                mail: {
                    required: true,
                    email1: true
                },
                
                current_pass: {
                	required: function(element){
                		var validateCurrentPass = false;
                		var currentEmail = $('.c-current-email').attr('data-cemail');
                		
                		if(currentEmail != $('input[name="mail"]').val())
                		{
                			validateCurrentPass = true;
                		}
                		
                		if( ($('input[name="pass[pass1]"]').val() > Number(0)) || ($('input[name="pass[pass2]"]').val() > Number(0)) )
                		{
                			validateCurrentPass = true;
                		}
                		return validateCurrentPass;
                	}
                }
        	},
        	
            focusCleanup: true,
            errorClass: "error",
            errorPlacement: function( label, element ) {
                label.addClass("c-error-msg-label");
                label.addClass("c-ate-error-validation-msg-" + element.attr("name"));
                if( element.attr( "type" ) === "checkbox" || element.attr( "type" ) === "radio" ) {
                    element.parent().append( label );
                }
                else {
                    label.insertAfter( element );
                }
            },
            
            messages: {
                name: {
                    required: Drupal.settings.flowdevmsg.errorrequired,
                    minlength: Drupal.settings.flowdevmsg.errorminlength
                },
                current_pass: {
                	required: Drupal.settings.flowdevmsg.errorpassword3
                },
                
                mail: {
                    required: Drupal.settings.flowdevmsg.errorrequired
                }
            }
        });
    },
    

    this.save_profile = function (e) {

    	//console.log('UserProfileForm::save_profile');
        var form = e.data._form;
        var newEmail = form.find('input[name="mail"]').val();
        var oldEmail = form.find('input[name="current_email"]').val();
        
        if(form.valid())
        {
            if (newEmail != oldEmail) {
                e.preventDefault();
                var emailWarning = Flowdeveloper.cloneJSTemplate('#email-update-warning-template');
                var elID = emailWarning.attr('data-modalid');
                var continueBtn = emailWarning.find('.c-continue-btn');

                emailWarning.attr('id', elID);
                continueBtn.click(function (e) {
                    emailWarning.modal('hide');
                    form.submit();
                });
                emailWarning.modal('show');
            }        	
        }

    }

}.call(UserProfileForm));
(function (){
    this.init_controls = function () {
        $ = jQuery;
        var Form = $('#flowdeveloper-device-delete-form, #flowdeveloper-device-list-form');
        if (Form.length > 0) {
            var saveBtn = Form.find('#edit-submit');
            saveBtn.bind('click', {_form: Form}, DeleteDeviceForm.showDeleteDeviceWarning);
            
            var deleteBtn = Form.find('.c-delete-device-btn');
            if(deleteBtn.length > Number(0))
            {
            	deleteBtn.bind('click', {_form: Form}, DeleteDeviceForm.showDeleteDeviceWarning);
            }
        }
    };
    
    this.showDeleteDeviceWarning = function (e) {
        var form = e.data._form;
        e.preventDefault();
        var deleteDeviceWarning = Flowdeveloper.cloneJSTemplate('#device-delete-warning-template');
        var elID = deleteDeviceWarning.attr('data-modalid');
        var continueBtn = deleteDeviceWarning.find('.c-continue-btn');
        var selectedDevices = '';
        
        $("input[type=checkbox].checkbox-primary.c-device-chk:checked").each(function(index){
        	selectedDevices = selectedDevices + $(this).attr('deviceid') + '|';
        });
        form.find("input[name='selected_devices']").val(selectedDevices);
        
        deleteDeviceWarning.attr('id', elID);
        continueBtn.click(function (e) {
            deleteDeviceWarning.modal('hide');
            form.submit();
        });
        
        var eventTarget = $(e.target);
        if(eventTarget.hasClass('c-delete-device-btn'))
        {
        	if(eventTarget.hasClass('q-active'))
        	{
        		deleteDeviceWarning.modal('show');
        	}	
        }
        else
        {
        	deleteDeviceWarning.modal('show');
        }
    }
}.call(DeleteDeviceForm));

(function (){
	
	this.init_controls = function(){

        var form = jQuery('#flowdeveloper-form-logs');
        if (form.length > 0)
        {
            var logType = form.find('select[name="log_type"]');
            logType.bind('change', {_form: form}, LogViewer.logtype_change_handler);
        }
    };
    
    this.logtype_change_handler = function(e){
    	var form = e.data._form;
    	var selectedLogType = form.find('select[name="log_type"]').val();
    	var component = jQuery('.c-log-entry-list');
    	var basePath = component.attr('data-basepath');
    	var currentPage = component.attr('data-currentpage');
    	var newurl = basePath +'/'+ selectedLogType +'/1';
    	//console.log('SelectedLogType: ' + selectedLogType);
    	//console.log('BasePath: ' + basePath);
    	//console.log('currentPage: ' + currentPage);
    	window.open(newurl, '_self');

    }
	
}.call(LogViewer)); /** Log viewer **/
/**
(function (){
	
	this.init_controls = function(){
		
		var $ = jQuery; 
        var configForm  = jQuery('#flowautho-admin-settings-form');
        if (configForm.length > 0)
        {
        	var lidSelect = configForm.find('select[name="flowautho_default_licensee"]');
        	var selectedOption = lidSelect.find(':selected').attr('value');
        	lidSelect.find('option[value="'+ selectedOption+'"]').attr('selected', true);
        	
        	lidSelect.change(function(e){
            	var selectedOption = $(this).find(':selected');
            	var comboValue = selectedOption.attr('value');
            	var valueArray = comboValue.split('#');
            	configForm.find('input[name="flowautho_webservice_key"]').val(valueArray[1]);
            	configForm.find('input[name="flowautho_webservice_secret"]').val(valueArray[2]);
        	});
        }
    }	
    
}.call(FlowAuthoModule)); **//** FlowAuthoModule functions **/
(function (){

    this.init_controls = function(){

        var appbuilder_container = $('#appbuilder-container'),
            appbuilder_pinned_dashboards_container = $('#appbuilder-pinned-dashboards-container');

        if(appbuilder_container.length > 0){
            this.dashboard_config_init();
        }
        else if(appbuilder_pinned_dashboards_container.length > 0){
            this.dashboard_landing_init();
        }

        //Initiate logout handler anyway -
        this.handleLogout();
    };
    this.dashboard_config_init = function(){

        //Get containers.
        var $appbuilder_container = $("#appbuilder-container"),
            $appbuilder_iframe = $appbuilder_container.find('iframe');

        // Little hack to get full height of the containers.
        $appbuilder_container.height($("body").height());
        $appbuilder_iframe.height($("body").height() - 10);
        $appbuilder_iframe.width($("body").width() - 230);


        //We also need to handle resizing.
        var widthRatio_iframe = $appbuilder_iframe.width() / $(window).width(),
            widthRatio_container = $appbuilder_container.width() / $(window).width();
        $(window).resize(function() {
            if($(window).width() > 768) {
                $appbuilder_iframe.css({width: $(window).width() - 230});
                $appbuilder_container.css({width: $(window).width() - 230 });
            }
            else{
                $appbuilder_iframe.css({width: $(window).width()});
                $appbuilder_container.css({width: $(window).width()});
            }

        });

        // Here we go.
        var $appbuilder_url = Drupal.settings.appbuilder.url;
        $appbuilder_iframe.attr("src", $appbuilder_url);


    };
    this.dashboard_landing_init = function(){

        //Get containers.
        var $appbuilder_container = $("#appbuilder-pinned-dashboards-container"),
            $appbuilder_iframe = $appbuilder_container.find('iframe');

        // Little hack to get full height of the containers.
        $appbuilder_container.height($("body").height());
        $appbuilder_iframe.height($("body").height() - 10);
        $appbuilder_iframe.width($("body").width() - 230);


        //We also need to handle resizing.
        var widthRatio_iframe = $appbuilder_iframe.width() / $(window).width(),
            widthRatio_container = $appbuilder_container.width() / $(window).width();
        $(window).resize(function() {
            if($(window).width() > 768) {
                $appbuilder_iframe.css({width: $(window).width() - 230});
                $appbuilder_container.css({width: $(window).width() - 230 });
            }
            else{
                $appbuilder_iframe.css({width: $(window).width()});
                $appbuilder_container.css({width: $(window).width()});
            }

        });

        // Here we go.
        var $appbuilder_pinned_dashboards_url = Drupal.settings.appbuilder.pinned_dashboards_url;
        $appbuilder_iframe.attr("src", $appbuilder_pinned_dashboards_url);


    };
    this.handleLogout = function(){
        /*
         When we initiate logging out from FDW, Dashboard builder should not stay logged in.
         */

        var $logout_url = Drupal.settings.appbuilder.logout_path;
        var $base_path = Drupal.settings.appbuilder.fdw_base_path;

        $('#user-logout-link').on("click", function(){
            jQuery.ajax({
                type: "GET",
                url: $logout_url,
                async: true,
                success: function(ajaxResponse){},
                error: function(e, jqxhr, ajaxOptions, thrownError){}
            });
        });
    };


}.call(AppBuilder)); /** App Builder related **/

/** Device Related **/
(function (){
    $ = jQuery;

    this.getStatuses = function(){

        init();

        var $devices = jQuery('.c-device').toArray(); //var $devices = jQuery('.c-device').toArray();
        var $devices_count = $devices.length;

        if($devices_count < 1) return;

        for(var $i=0; $i < $devices_count; $i++){
            var $device = jQuery($devices[$i]);
            if($device.hasClass("c-device") && $device.attr("data-is-manageable") == "true"){
                getDeviceStatus($device.attr("data-device-id"));
            }
        }

    };
    function init(){

        /**
         * Nested functions
         */

        function closeEditForm(e, updatedName, updateDescription){
            // Retrieve fields
            var $nameField = $('.c-device-name-field-value'),
                $descriptionField = $('.c-device-description-field-value'),
                $deviceName = $('.c-edit-device-name-input').attr("value"),
                $deviceDescription = $descriptionField.text(),
                $editBtns = $('.c-device-detail-edit-btns');


            if(typeof updatedName !== 'undefined'){
                if(updatedName.length > 0) {
                    $deviceName = updatedName;
                    $('.c-dashboard-title').html(updatedName);
                }
            }

            if(typeof updatedName !== 'undefined') {
                if(updateDescription.length > 0) $deviceDescription = updateDescription;
            }

            $('.c-tab-edit-icon').removeClass("active");

            //Remove forms
            $nameField.html($deviceName);
            $descriptionField.html($deviceDescription);

            //Hide buttons
            $editBtns.css("display", "none");
            //and disable submit for later use
            $('.c-device-detail-edit-update').attr("disabled","disabled").addClass("disabled");
        }
        function openEditForm(e){
            // Retrieve fields
            var $nameField = $('.c-device-name-field-value'),
                $descriptionField = $('.c-device-description-field-value'),
                $deviceName = $nameField.text(),
                $deviceDescription = $descriptionField.text(),
                $editBtns = $('.c-device-detail-edit-btns');


            $('.c-tab-edit-icon').addClass("active");

            //Inject forms
            $nameField.html('<input class="c-edit-device-name-input" type="text" value="' + $deviceName + '"/>');
            $descriptionField.html('<textarea class="c-edit-device-description-input" rows="4" cols="50">' + $deviceDescription + '</textarea>');

            //Show buttons
            $editBtns.css("display", "block");

        }

        /**
         * Click Handlers - Devices
         */

        $('#c-tab-device-edit-icon').on("click", function(event){
            event.stopPropagation();
            if($(this).hasClass("active")){ closeEditForm($(this)); }
            else{ openEditForm($(this)); }
        });
        $('.c-device-detail-edit-cancel').on("click", function (event) {
            event.stopPropagation();
            closeEditForm($(this));
        });
        $('.c-device-detail-edit-update').on("click", function (event) {
            event.stopPropagation();

            // Retrieve fields
            var $updatedName = $('.c-edit-device-name-input').val(),
                $updatedDescription = $('.c-edit-device-description-input').val(),
                $deviceID = $(this).attr("data-device-id"),
                $editBtns = $('.c-device-detail-edit-btns');
            
            var ajaxURL = Drupal.settings.basePath + UPDATE_DEVICE_INFO_ENDPOINT + "/" + $deviceID;
            var ajaxData = {_deviceid: $deviceID, _newname: $updatedName, _newdesc: $updatedDescription};

            $.ajax({
                type: 'POST',
                async: true,
                url: ajaxURL,
                data: ajaxData,
                error: function() {
                    alert("That didn't seem to work, please try again");
                },
                success: function(data) {
                    if(data == true){
                        closeEditForm($(this), $updatedName, $updatedDescription);
                        $(".c-ate-is-loaded").addClass('c-ate-loaded');
                    }
                    else if(data == false){
                        $(".c-ate-is-loaded").addClass('c-ate-loaded');
                        alert("That didn't seem to work, please try again");
                    }
                }
            });
        });
        $('.c-device-name-field-value, .c-device-description-field-value').on("click", function (event) {
            event.stopPropagation();
        });

        var html = $('html');

        html.on("click", function () {
            if($('.c-tab-actual-content').length) {
                closeEditForm($(this));
            }


        });
        $('.c-device-icon .checkbox-primary').on("click", function () {
        	
           // $('.c-devices-back-deselect-button').css("display", "block");
            if($(this).hasClass("select-all-checkbox")) return;
            if($(this).is(':checked')) 
            {
                $('.c-device-list-status-icon').addClass('c-device-status-hidden');
                $('input[type=checkbox].checkbox-primary + label').addClass('checkbox-shown');
                $('input[type=checkbox].checkbox-primary:checked + label').addClass('c-ate-chk-checked');
                $('.c-delete-device-btn').addClass('q-active');
            } 
            else 
            {
                if( $("input[type=checkbox].checkbox-primary.c-device-chk:checked").length == 0)
                {
                    $('.c-select-all-checkbox input').each(function(i,v){
                        v.checked = false;
                    });

                    $('.c-device-list-status-icon').removeClass('c-device-status-hidden');
                    $('input[type=checkbox].checkbox-primary + label').removeClass('checkbox-shown c-ate-chk-checked');
                    $('.c-devices-back-deselect-button').css("display", "none");
                    
                } else {
                    $(this).next().removeClass('c-ate-chk-checked');
                }
            }
            $('.c-device-count').val($("input[type=checkbox].checkbox-primary:checked").length);
            
            if($("input[type=checkbox].checkbox-primary:checked").length < Number(1))
            {
            	$('.c-delete-device-btn').removeClass('q-active');
            }
        });

        $('.c-select-all-checkbox input').on("change", function(){
            if($(this).is(":checked") == true) {
                $('.c-device-icon .checkbox-primary').each(function(i,v){
                    v.checked = true;
                });
                $('.c-device-list-status-icon').addClass('c-device-status-hidden');
                $('input[type=checkbox].checkbox-primary + label').addClass('checkbox-shown c-ate-chk-checked');

                $('.c-devices-back-deselect-button').css("display", "block");
            }
            else {
                $('.c-device-icon .checkbox-primary').each(function(i,v){
                    v.checked = false;
                });
                $('.c-device-list-status-icon').removeClass('c-device-status-hidden');
                $('input[type=checkbox].checkbox-primary + label').removeClass('checkbox-shown c-ate-chk-checked');

                $('.c-devices-back-deselect-button').css("display", "none");
            }
            
            if($("input[type=checkbox].checkbox-primary:checked").length < Number(1))
            {
            	$('.c-delete-device-btn').removeClass('q-active');
            }
        });

        $('.c-devices-back-deselect-button').on("click", function(){
            $('.c-device-icon .checkbox-primary').each(function(i,v){
                v.checked = false;
            });
            $('.c-select-all-checkbox input').each(function(i,v){
                v.checked = false;
            });
            $('.c-device-list-status-icon').removeClass('c-device-status-hidden');
            $('input[type=checkbox].checkbox-primary + label').removeClass('checkbox-shown c-ate-chk-checked');

            $(this).css("display", "none");
            $('.c-devices-select-all-link').css("display", "block");
        });

        $('.c-device-managed:not(.c-no-refresh), .c-device-unmanaged:not(.c-no-refresh)').mouseenter(function() {
            $(this).addClass('c-ate-device-mouseover');
        });
        $('.c-device-managed:not(.c-no-refresh), .c-device-unmanaged:not(.c-no-refresh)').mouseleave(function() {
            $(this).removeClass('c-ate-device-mouseover');
        });

        $('.c-hak-iot-signup').on("click", function (event) {
            Flowdeveloper.setCookie("LoginRedirect","dashboard/devices/registerd",null);
        });

    }
    function getDeviceStatus($deviceID){
        //Let's retrieve the device DOM element
        var $device = $("a[data-device-id='" + $deviceID + "']");

        var $device_status_icon = $device.next();
        var $device_status_text = $device.find(".c-device-list-status-info");

        var status = null;

        $.ajax({
            type: 'GET',
            async: true,
            url: Drupal.settings.basePath + RETRIEVE_DEVICE_STATUS_ENDPOINT + "/" + $deviceID,
            error: function() {
                //return an error code: The theme should know what to make of it.
                $device_status_icon.removeClass('c-device-default-status-icon');
                $device_status_icon.addClass('c-device-status-offline');
                $device_status_text.html(status.LastSeenTime);
            },
            success: function(data) {
                status = JSON.parse(data);

                if(status.Online == true) {
                    $device_status_icon.removeClass('c-device-default-status-icon');
                    $device_status_icon.addClass('c-device-status-online');
                    $device_status_text.html('Online');
                }
                else {
                    $device_status_icon.removeClass('c-device-default-status-icon');
                    $device_status_icon.addClass('c-device-status-offline');
                    $device_status_text.html(status.LastSeenTime);
                }
            }
        });

        //return status;
    }

}.call(fdw_devices));
(function (){

    this.init_controls = function(){

        var $ = jQuery;
        var deleteDeviceBtn = $('.c-alt-delete-device-btn');
        if(deleteDeviceBtn.length > 0)
        {
            var modalid = 'delete-single-device-warning';
            deleteDeviceBtn.bind('click', {_modalid:modalid}, DeviceDetails.showDeleteDeviceWarning);
        }
    },

        this.showDeleteDeviceWarning = function (e) {

            var $ = jQuery;
            e.preventDefault();
            var modalid = e.data._modalid;
            var deleteDeviceWarning = Flowdeveloper.cloneJSTemplate('#delete-single-device-warning-template');
            var elID = deleteDeviceWarning.attr('data-modalid');
            var continueBtn = deleteDeviceWarning.find('.c-continue-btn');
            var cancelBtn = deleteDeviceWarning.find('.c-cancel-btn');
            var target = $(e.target).parents('a.q-delete-device').attr('href');
            var targetURL = window.location.protocol+'//'+window.location.hostname+target;

            deleteDeviceWarning.attr('id', elID);
            cancelBtn.click(function(e){
                deleteDeviceWarning.modal('hide');
            });
            continueBtn.click(function (e) {
                deleteDeviceWarning.modal('hide');
                window.location.href = targetURL;
            });

            deleteDeviceWarning.modal('show');
        }

    this.renderGeoLocation = function(){

        var $ = jQuery;
        var mapDiv = $('#device-geo-location-map');
        var latitude = Number(mapDiv.attr('data-lat'));
        var longitude = Number(mapDiv.attr('data-long'));
        var mapContainer = document.getElementById('device-geo-location-map');
        //latitude = Number(51.706);
        //longitude = Number(-0.440);
        var map = new google.maps.Map(mapContainer, {
            center: {lat: latitude, lng: longitude},
            zoom: 8
        });

        var geocoder = new google.maps.Geocoder;
        var locationObject = {lat: latitude, lng: longitude};
        geocoder.geocode({'location': locationObject}, function(results, status){
            if (status === google.maps.GeocoderStatus.OK)
            {
                //console.log(results);
                if (results[1])
                {
                    $('#device-geo-location-address').html(results[1].formatted_address);
                    $('#device-geo-location-address').attr('alt', results[1].formatted_address);
                    $('#device-geo-location-address').attr('title', results[1].formatted_address);
                    //console.log(results[1].formatted_address);
                }
            }
        });

        //console.log('Google Maps API is ready to use:: LAT: ' + latitude + ', LONG: '+ longitude);
    }

}.call(DeviceDetails));
(function (){

    this.init_controls = function(){

        var resourceObjects  = jQuery('#device-resources .c-resource-object');
        if (resourceObjects.length > 0)
        {
            resourceObjects.each(function(index){

                var _self = jQuery(this);
                if(_self.hasClass('q-multiple'))
                {
                    //_self.bind('click', {_ro: _self}, DeviceResources.resource_object_click_handler);
                    _self.find('.c-header-wrapper').bind('click', {_ro: _self}, DeviceResources.resource_object_click_handler);
                }
                else if (_self.hasClass('q-single'))
                {
                    //_self.bind('click', {_ri:_self}, DeviceResources.toggle_resource_state);
                    _self.find('.c-header-wrapper').bind('click', {_ri:_self}, DeviceResources.toggle_resource_state);
                }
            });

        }
    },

        this.resource_object_click_handler = function(e){

            var _self = e.data._ro;

            if(_self.hasClass('s-active'))
            {
                DeviceResources.deactivate_all();
            }
            else
            {
                DeviceResources.deactivate_all();
                _self.addClass('s-active');
                /**
                 * Bind Click events
                 */
                jQuery('.c-resource-object.s-active .cp-instances .c-resource-instance').each(function(index){
                    var _iself = $(this);
                    //console.log('[resource_object_click_handler::] Re-bind Click event for');
                    //console.log(_iself);
                    //_iself.unbind('click');
                    //_iself.bind('click', {_ri:_iself}, DeviceResources.toggle_resource_state);

                    _iself.find('.c-header-wrapper').unbind('click');
                    _iself.find('.c-header-wrapper').bind('click', {_ri:_iself}, DeviceResources.toggle_resource_state);
                });
            }
        },

        this.load_resource_instance_handler = function(e){

            var _self = e.data._ri;
            var roid = _self.attr('data-roid');
            var riid = _self.attr('data-iid');
            var did = _self.attr('data-deviceid');

            ajaxURL = Drupal.settings.basePath + FDW_AJAX + '/' +  FDW_DEVICE + '/' + did + '/' + FDW_RESOURCES + '/' + roid + '/' + riid;


            if(_self.hasClass('q-single'))
            {
                DeviceResources.deactivate_all();
                _self.addClass('s-active');
                _self.find('.cp-instances .c-resource-instance').addClass('s-active');
            }
            else
            {
                jQuery('#device-resources .c-resource-object.s-active .cp-instances .c-resource-instance').removeClass('s-active');
                _self.addClass('s-active');
            }
            e.stopPropagation();
            jQuery.ajax({
                type: "GET",
                url: ajaxURL,
                dataType: 'html',
                success: function(ajaxResponse){

                    if(_self.hasClass('q-single'))
                    {
                        _self.find('.cp-instances .c-resource-instance .cp-details').html(ajaxResponse);
                    }
                    else
                    {
                        _self.find('.cp-details').html(ajaxResponse);
                    }

                    //console.log(_self.find('.c-refresh-instance > span'));
                    _self.find('.c-refresh-instance > .c-refresh-resource-instance-btn').on('click', function(refreshEvent){
                        _self.find('.cp-details').html(Flowdeveloper.cloneJSTemplate('#ajax-refresh-preloader-template'));
                        jQuery(this).remove();
                        DeviceResources.load_resource_instance_handler(e);
                    });
                },
                error: function(e, jqxhr, ajaxOptions, thrownError){

                }
            });
        } ,

        this.deactivate_all = function(){

            var resourceObjects = jQuery('#device-resources .c-resource-object');
            resourceObjects.removeClass('s-active');
            resourceObjects.find('.cp-instances .c-resource-instance').removeClass('s-active');
        },

        this.toggle_resource_state = function(e){

            var $ = jQuery;
            var _self = e.data._ri;

            //console.log(_self);
            if(_self.hasClass('c-resource-object'))
            {
                if(_self.hasClass('s-active'))
                {
                    DeviceResources.deactivate_all();
                }
                else
                {
                    DeviceResources.load_resource_instance_handler(e);
                }
            }
            else
            {
                if(_self.hasClass('s-active'))
                {
                    //console.log('[toggle_resource_state::] Fold Instance');
                    _self.removeClass('s-active');
                    e.stopPropagation();
                }
                else
                {
                    //console.log('[toggle_resource_state::] About to Load Instance');
                    DeviceResources.load_resource_instance_handler(e);
                }
            }
        }


}.call(DeviceResources));
(function (){

	this.init_controls = function(){
		
		var $ = jQuery; 
		var deviceReg = $('.cn-device-reg');
		if(deviceReg.length > 0)
		{
			var cookiename = Drupal.settings.flowdevuser.fcapcodeCookieName;
			var gotitCookie = Flowdeveloper.getCookie(cookiename);
			if(gotitCookie == '1')
			{
				$('.cn-device-reg .cp-help').css('display', 'none');
			}
			
			//console.log('[DeviceRegistration::init_controls] Got it CookieName: ' + cookiename);
			//console.log(gotitCookie);
			
			deviceReg.find('.cp-help .c-got-it-btn').bind('click', function(e){
				var cookieValue = '1';
				Flowdeveloper.setCookie(cookiename, cookieValue, 1065);
				$('.cn-device-reg .cp-help').css('display', 'none');
			});
			
			var form = $('#flowdeveloper-device-registration-form');
		    var deviceType = form.find('select[name="device_type"]');
		    deviceType.bind('change', {_form: form}, DeviceRegistration.show_registration_guide);
		}
	}
	
	this.show_registration_guide = function(e){
		
		var $ = jQuery; 
		var form = e.data._form;
		var selectedDeviceType = form.find('select[name="device_type"]').val();
		var guideContainer = $('.cn-device-reg .c-devicereg-instruction');
	    ajaxURL = Drupal.settings.basePath + FDW_AJAX + '/' + FDW_DEVICES + '/' + FDW_REG_GUIDE +'/' + selectedDeviceType;
	    guideContainer.css('display', 'block').html(Flowdeveloper.cloneJSTemplate('#ajax-preloader-template'));
	    
		jQuery.ajax({ 
			type: "GET", 
			url: ajaxURL, 
			dataType: 'html', 
			success: function(ajaxResponse){
				guideContainer.html(ajaxResponse);
			},
			error: function(e, jqxhr, ajaxOptions, thrownError){
    		}
    	});		    
	}
	
}.call(DeviceRegistration));


/**
 * Ready signal.
 * Uses jQuery instead of $ as it is executed before the definition.
 * Rest of the file can use $.
 * Can also be used to provide QA with a ready signal as this is the (should be) last JS file that gets loaded.
 **/
jQuery(document).ready(function(){

    /**
     * Initiate SIP
     */

    fdw_sip.init_controls();


    /**
     * Initiate controls for forms.
     */
    PasswordIssuesForm.init_controls();
    UserProfileForm.init_controls();
    DeleteDeviceForm.init_controls();
    RegisterForm.init_controls();
    LoginForm.init_controls();
    LogViewer.init_controls();
    
    DeviceResources.init_controls();
    FlowAuthoModule.init_controls();
    if(Drupal.settings.appbuilder.enabled) AppBuilder.init_controls();
    DeviceRegistration.init_controls();
    DeviceDetails.init_controls();
    

    /**
     * Initiate device status retrieval for all devices
     */
    fdw_devices.getStatuses();


    /**
     * Handle is_page_active
     */

    $(window).focus(function() { is_page_active = true;});
    $(window).blur(function() { is_page_active = false; });

});
