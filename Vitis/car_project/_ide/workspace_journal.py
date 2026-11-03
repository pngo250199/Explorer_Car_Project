# 2026-11-02T13:43:45.387842850
import vitis

client = vitis.create_client()
client.set_workspace(path="car_project")

platform = client.create_platform_component(name = "linux_platform",hw_design = "$COMPONENT_LOCATION/../../../Vivado/Car_project/car_hardware_export.xsa",os = "standalone",cpu = "ps7_cortexa9_0",domain_name = "standalone_ps7_cortexa9_0",compiler = "gcc")

platform = client.get_component(name="linux_platform")
status = platform.build()

comp = client.create_app_component(name="car_baremetal",platform = "$COMPONENT_LOCATION/../linux_platform/export/linux_platform/linux_platform.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="car_baremetal")
status = comp.clean()

comp.build()

status = comp.clean()

comp.build()

comp.build()

status = comp.clean()

comp.build()

comp.build()

vitis.dispose()

