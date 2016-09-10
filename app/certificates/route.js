import Ember from 'ember';

export default Ember.Route.extend({
    model(){
        
    },
    actions: {
        generate_certificate: function (params) {
            var dialog = document.querySelector('dialog');
            dialog.showModal();
        },
        close_modal: function (params) {
            var dialog = document.querySelector('dialog');
            dialog.close();
        },
        copy_certificate: function (params) {
            var certificate = document.getElementById('certificate-' + params),
                range = document.createRange();
                range.selectNodeContents(certificate); // set range to encompass desired element text
            
            var selection = window.getSelection(); // get Selection object from currently user selected text
            selection.removeAllRanges(); // unselect any user selected text (if any)
            selection.addRange(range); // add range to Selection object to select it
            document.execCommand("Copy", false, null);
        }
    }
});
