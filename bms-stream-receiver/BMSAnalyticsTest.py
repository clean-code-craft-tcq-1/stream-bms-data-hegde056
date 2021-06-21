import unittest
import BmsMonitor


class BMSAnalyticsTest(unittest.TestCase):
  def test_valid_line(self):
      self.assertTrue(BmsMonitor.isValidLine('20:46') == False)

  def test_simple_moving_average(self):
      #Check simple moving average of temperature and soc parameters
      BmsMonitor.temperature_buffer = [11,22,33,44,55]
      BmsMonitor.soc_buffer = [10,20,30,40,50]
      self.assertTrue(BmsMonitor.getTemperatureSMA() == 33)
      self.assertTrue(BmsMonitor.getSocSMA() == 30)
      
  def test_temperature_and_soc_buffer_save(self):
      #Check whether temperature and soc buffer is saved    
      self.assertTrue(len(BmsMonitor.temperature_buffer) == 5)
      self.assertTrue(len(BmsMonitor.soc_buffer) == 5)
      
  def test_display_bms_analytics(self):
      #Check display of BMS analytics    
      BmsMonitor.displayBMSAnalytics('30,50')
      
  def test_max_and_min_bms_parameters(self):
      #Check maximum and minimum temperature and soc parameters   
      self.assertTrue(BmsMonitor.getMaximumTemperature(10) == 55)
      self.assertTrue(BmsMonitor.getMinimumTemperature(20) == 11)
      self.assertTrue(BmsMonitor.getMaximumSOC(40) == 50)
      self.assertTrue(BmsMonitor.getMinimumSOC(20) == 10)
      
if __name__ == '__main__':
  unittest.main()
