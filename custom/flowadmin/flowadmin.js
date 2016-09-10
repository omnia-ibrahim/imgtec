/**
 * Define namespaces
 */
var FMTopicsForm = {}, Datastores = {};

(function(){
	
	 this.init_controls = function(){
		 
		 var $ = jQuery; 
		 var topicsForm = $('#flowadmin-topic-form');
		 if(topicsForm.length > 0)
		 {
			 var useEventHistory = topicsForm.find('input[name="use_event_history"]');
			 useEventHistory.bind('click', {_form: topicsForm}, FMTopicsForm.use_event_history_handler);
		 }
		 
		 var topicList = $('.topics-list-wrapper');
		 if(topicList.length > 0)
		 {
			 $('.c-list-item .p-actions .c-control.q-delete').each(function(index){
				 $(this).bind('click', FMTopicsForm.showDeleteTopicWarning);
			 });
		 }
	 },
	 
	 this.use_event_history_handler = function(e){
		 var $ =  jQuery;
		 var form = e.data._form;
		 var maxAgeField = form.find('.form-item-maxage.form-item');
		 if($(e.target).is(':checked'))
		 {
			 FMTopicsForm.show_max_age(maxAgeField);
		 }
		 else
		 {
			 FMTopicsForm.hide_max_age(maxAgeField);
		 }
	 },
	 
	 this.show_max_age = function(maxAgeField){
		 if(maxAgeField.css('display') == 'none')
		 {
			 maxAgeField.show();
		 }
	 },
	 
	 this.hide_max_age = function(maxAgeField){
		 if(maxAgeField.css('display') == 'block')
		 {
			 maxAgeField.hide(); 
		 }
	 },
	 
     this.showDeleteTopicWarning = function (e) {

         var $ = jQuery;
         e.preventDefault();
         var deleteTopicWarning = Flowdeveloper.cloneJSTemplate('#topic-delete-warning-template');
         var elID = deleteTopicWarning.attr('data-modalid');
         var continueBtn = deleteTopicWarning.find('.c-continue-btn');
         var cancelBtn = deleteTopicWarning.find('.c-cancel-btn');
         var target = $(e.target).attr('href');
         var targetURL = window.location.protocol+'//'+window.location.hostname+target;
         
         deleteTopicWarning.attr('id', elID);
         cancelBtn.click(function(e){
        	 deleteTopicWarning.modal('hide');
         });
         continueBtn.click(function (e) {
        	 deleteTopicWarning.modal('hide');
             window.location.href = targetURL;
         });

         deleteTopicWarning.modal('show');
     }	 
	 
}.call(FMTopicsForm));

/**
 * Datastores related js functions
 */
(function(){

	this.init_controls = function(){
		 
		 var $ = jQuery; 
		 var datastoreList = $('.datastores-list-wrapper');
		 if(datastoreList.length > 0)
		 {
			 $('.c-list-item .p-actions .c-control.q-delete').each(function(index){
				 $(this).bind('click', Datastores.showDeleteTopicWarning);
			 });
		 }	
	},
	 
    this.showDeleteTopicWarning = function (e) {

        var $ = jQuery;
        e.preventDefault();
        var deleteDatastoreWarning = Flowdeveloper.cloneJSTemplate('#datastore-delete-warning-template');
        var elID = deleteDatastoreWarning.attr('data-modalid');
        var continueBtn = deleteDatastoreWarning.find('.c-continue-btn');
        var cancelBtn = deleteDatastoreWarning.find('.c-cancel-btn');
        var target = $(e.target).attr('href');
        var targetURL = window.location.protocol+'//'+window.location.hostname+target;
        
        deleteDatastoreWarning.attr('id', elID);
        cancelBtn.click(function(e){
        	deleteDatastoreWarning.modal('hide');
        });
        continueBtn.click(function (e) {
        	deleteDatastoreWarning.modal('hide');
            window.location.href = targetURL;
        });

        deleteDatastoreWarning.modal('show');
    }	
	
}.call(Datastores));

/**
 * Ready signal.
 * Uses jQuery instead of $ as it is executed before the definition.
 * Rest of the file can use $.
 * Can also be used to provide QA with a ready signal as this is the (should be) last JS file that gets loaded.
 **/
jQuery(document).ready(function(){
	
	FMTopicsForm.init_controls();
	Datastores.init_controls();
});