from pydantic import BaseModel
from datetime import datetime


class TicketByTrainTypeSchema(BaseModel):
    train_type: str
    total_tickets: int


class AvgPriceByRouteSchema(BaseModel):
    departure_station: str
    arrival_station: str
    average_price: float


class SeatsByCarTypeSchema(BaseModel):
    car_type: str
    total_seats: int


class PopularRouteSeasonSchema(BaseModel):
    season: str
    departure_station: str
    arrival_station: str
    passengers: int


class TrainRatingByCarTypeSchema(BaseModel):
    train_number: str
    train_type: str
    car_type: str
    sold_tickets: int


class TrainFromAToBSchema(BaseModel):
    train_number: str
    train_type: str
    departure: datetime
    arrival: datetime
