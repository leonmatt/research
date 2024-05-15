# maitnenace test business logic

#def test_maintenance(temperature:int):
def test_maintenance(hydraulic_pressure:int):
    """_summary_

    Parameters
    ----------
    hydraulic_pressure : int
        test parameter for hydraulic_pressure sensor readings

    Returns
    -------
    str
        'Approved' or 'Denied' based on hydraulic_pressure readings
    """

    # Change 1 in the lab is to adjust the upper limit for hydraulic_pressure to 2000
    #maintenance_status = 'Needs Maintenance' if hydraulic_pressure > 50 else 'No Maintenance Required'
    maintenance_status = 'Needs Maintenance' if hydraulic_pressure > 2000 else 'No Maintenance Required'

    return maintenance_status

def get_help(input_string:str):
    return "bring the harvester in for maintenance" if input_string == "help" else "Looks Like help is not needed from supportbot"