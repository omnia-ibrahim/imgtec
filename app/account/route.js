import Ember from 'ember';

export default Ember.Route.extend({
    model(){
        
    },
    actions: {
        didTransition: function() {
            Ember.run.scheduleOnce('afterRender', this, function() {
                setTimeout(function() {
                    var tabs = Ember.$('.mdl-tabs')[0],
                        fields = Ember.$('.mdl-textfield').toArray();
                        
                    componentHandler.upgradeElement(tabs);                     
                    componentHandler.upgradeElements(fields);
                    
                    return true; // Bubble the didTransition event
                });
            });
        }
    }
});
