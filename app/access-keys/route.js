import Ember from 'ember';

export default Ember.Route.extend({
    model(){
        
    },
    actions: {
        generate_access_key: function (params) {
            var dialog = document.querySelector('dialog');
            dialog.showModal();
        },
        close_modal: function (params) {
            var dialog = document.querySelector('dialog');
            dialog.close();
        },
         didTransition: function() {
            Ember.run.scheduleOnce('afterRender', this, function() {
                setTimeout(function() {
                    var textField = Ember.$('.mdl-textfield').toArray();
                    componentHandler.upgradeElements(textField);
                    
                    return true; // Bubble the didTransition event
                });
            });
        },
         copy_access_key: function (params) {
            var certificate = document.getElementById('access-key-' + params),
                range = document.createRange();
                range.selectNodeContents(certificate); // set range to encompass desired element text
            
            var selection = window.getSelection(); // get Selection object from currently user selected text
            selection.removeAllRanges(); // unselect any user selected text (if any)
            selection.addRange(range); // add range to Selection object to select it
            document.execCommand("Copy", false, null);
        }
    }
});