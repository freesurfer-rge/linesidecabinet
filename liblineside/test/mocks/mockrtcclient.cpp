#include "mockrtcclient.hpp"

void MockRTCClient::SendTrackCircuitNotification( const Lineside::ItemId trackCircuitId,
						  const bool occupied ) {
  this->lastItemId = trackCircuitId;
  this->lastOccupied = occupied;
}
