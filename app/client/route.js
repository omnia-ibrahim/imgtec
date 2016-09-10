import Ember from 'ember';

export default Ember.Route.extend({
    flow: Ember.inject.service('flow-api'),
    client_id: null,
    model(params){
        var flow = this.get('flow');
        this.set('client_id', params.client_id);
        return flow.get_client_details(this.get('client_id'));
    },
    actions: {
        didTransition: function() {
            Ember.run.scheduleOnce('afterRender', this, function() {
                setTimeout(function() {
                    var tabs = Ember.$('.mdl-tabs')[0];
                    componentHandler.upgradeElement(tabs);                     
                    return true; // Bubble the didTransition event
                });
            });
        }
    }
});

