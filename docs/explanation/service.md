(explanation-service)=
# Service

> See also: [Command-line interface](/reference/command-line-interface/index), [GUI client](/reference/gui-client), [Instance](/explanation/instance)

In Multipass, **service** refers to the Multipass server that clients connect to and that controls and manages Multipass instances. This can also be referred to as the **daemon**.

The Multipass daemon (`multipassd`) runs in the background and processes the requests from the Multipass [command-line interface](/reference/command-line-interface/index) and [GUI client](/reference/gui-client). The daemon is also in charge of the lifecycle of Multipass [instances](/explanation/instance). 

The separation between client (CLI or GUI) and daemon is a popular architecture because of its main advantage, that is, flexibility. For instance, the daemon process can be on a different machine from the client; see [Use Multipass remotely](https://discourse.ubuntu.com/t/how-to-use-multipass-remotely/26360) for more details.

The automatic start of the daemon process is triggered right after the Multipass installation. After that, it is also set up to start automatically at system boot. This setup ensures that the Multipass client can immediately interact with the instances without the need to launch the daemon manually, and restores any persistent instances of Multipass after a system restart.

---

*Errors or typos? Topics missing? Hard to read? <a href="https://docs.google.com/forms/d/e/1FAIpQLSd0XZDU9sbOCiljceh3rO_rkp6vazy2ZsIWgx4gsvl_Sec4Ig/viewform?usp=pp_url&entry.317501128=https://canonical.com/multipass/docs/service" target="_blank">Let us know</a> or <a href="https://github.com/canonical/multipass/issues/new/choose" target="_blank">open an issue on GitHub</a>.*
