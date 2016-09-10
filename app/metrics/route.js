import Ember from 'ember';

export default Ember.Route.extend({
    // flow: Ember.inject.service('flow-api'),
    model(){                
        return Ember.$.parseJSON(' [ { "Links": [ { "rel": "self", "href": "/metrics/6e544ae6-0486-4056-acc9-4b5ace140d05" } ], "Name": "NumberClients", "Value": 10 }, { "Links": [ { "rel": "self", "href": "/metrics/6e544ae6-0486-4056-acc9-4b5ace140d05" } ], "Name": "NumberTransactions", "Value": 19313 }, { "Links": [ { "rel": "self", "href": "/metrics/6e544ae6-0486-4056-acc9-4b5ace140d05" } ], "Name": "NumberOfBytesSent", "Value": 239012380123 } ]');
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
