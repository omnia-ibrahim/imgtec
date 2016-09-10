import Ember from 'ember';

export default Ember.Component.extend({
    keyUp: function (e) {     
        var re = new RegExp(Ember.$('input#page-search').val(), "i"); 
        Ember.$('tr.client-row').show().filter(function() {
            return !re.test($(this).text());
        }).hide();
    }
});
