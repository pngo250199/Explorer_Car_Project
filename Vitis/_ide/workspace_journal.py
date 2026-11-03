# 2026-11-02T12:56:53.564555040
import vitis

client = vitis.create_client()
client.set_workspace(path="Vitis")

comp = client.create_app_component(name="car_project",platform = "$COMPONENT_LOCATION/../../Vivado/Car_project/car_hardware_export.xsa",domain = "xrt")

comp = client.get_component(name="car_project")
comp.build()

comp.build()

vitis.dispose()

