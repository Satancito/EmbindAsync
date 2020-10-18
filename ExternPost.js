window.CreateModuleInstance({ noInitialRun: false })
    .then(instance => {
        window.Main = { Module: instance };
    });