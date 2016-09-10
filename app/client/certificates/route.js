import Ember from 'ember';

export default Ember.Route.extend({
    flow: Ember.inject.service('flow-api'),
    model(){        
        var flow = this.get('flow'),
            client_id = this.paramsFor('client').client_id;
            
        return flow.get_client_property(client_id, "certificates");
       
    },
   actions: {
        didTransition: function() {
            Ember.run.scheduleOnce('afterRender', this, function() {
                setTimeout(function() {
                        var fields = Ember.$('.mdl-textfield').toArray();
                        componentHandler.upgradeElements(fields);
                    
                        return true; // Bubble the didTransition event
                });
            });
        }
    }
});
