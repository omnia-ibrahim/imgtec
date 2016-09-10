import Ember from 'ember';
import AuthenticatedRouteMixin from 'ember-simple-auth/mixins/authenticated-route-mixin';

export default Ember.Route.extend(AuthenticatedRouteMixin,{
    flow: Ember.inject.service('flow-api'), 
    model() {        
        var flow = this.get('flow');
        return flow.get_clients();
    }, 
    actions: {
        didTransition: function() {
            Ember.run.scheduleOnce('afterRender', this, function() {
                setTimeout(function() {
                    var table = Ember.$('.mdl-data-table')[0],
                        search = Ember.$('.mdl-textfield').toArray(),
                        menuBtn = Ember.$('.mdl-button--icon')[0],
                        menu = Ember.$('.mdl-menu').toArray();
                        
                    componentHandler.upgradeElement(table); //remember to include this globally so
                    componentHandler.upgradeElements(search);
                    componentHandler.upgradeElement(menuBtn);
                    componentHandler.upgradeElements(menu);
                    
                     
                    return true; // Bubble the didTransition event
                });
            });
        }
    }
});