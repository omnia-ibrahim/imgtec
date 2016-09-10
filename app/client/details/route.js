import Ember from 'ember';

export default Ember.Route.extend({
    flow: Ember.inject.service('flow-api'),
    model(){        
        var flow = this.get('flow'),
            client_id = this.paramsFor('client').client_id;
            
        return flow.get_client_property(client_id, "self");
    }
});
