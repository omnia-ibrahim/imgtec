import Ember from 'ember';

export default Ember.Route.extend({
    model(){
        // Temporary hack to make index /metrics
       this.transitionTo('metrics');
    }
});
