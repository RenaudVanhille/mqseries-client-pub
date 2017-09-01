const pub = require('./build/Release/mq_pub.node');

function SendPub(i) {
        return new Promise(
                (resolve, reject) => {
                        pub.send('message ' + i).then(
                                () => { setTimeout(() => { return SendPub(++i); }, 1000) },
                                (reason) => { reject(reason); }
                        );
                }
        );
}

pub.init('QM2', 'sport').then(
        () => { SendPub(0).then(
                () => {},
                (reason) => {console.error(reason); }
        ); },
        (reason) => { console.error(reason); }
);