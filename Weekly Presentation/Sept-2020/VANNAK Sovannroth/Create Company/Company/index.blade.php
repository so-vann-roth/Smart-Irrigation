@extends('admin::layouts.master')
@section('header')
    <strong>Company Info</strong>
@endsection
@section('content')
    <div class="card card-gray">
        <div class="toolbox">
            <a href="{{route('company.edit', $com->id)}}" class="btn btn-success btn-sm btn-oval">
                <i class="fa fa-edit"></i> Edit
            </a>
        </div>
        <div class="card-block">
            @component('admin::coms.alert')
            @endcomponent
            <div class="row">
                <div class="col-sm-7">
                    <div class="form-group row">
                        <label class="col-sm-3">Name</label>
                        <div class="col-sm-9">
                            : {{$com->name}}
                        </div>
                    </div>
                    <div class="form-group row">
                        <label class="col-sm-3">Phone</label>
                        <div class="col-sm-9">
                            : {{$com->phone}}
                        </div>
                    </div>
                    <div class="form-group row">
                        <label class="col-sm-3">Email</label>
                        <div class="col-sm-9">
                            : {{$com->email}}
                        </div>
                    </div>
                    <div class="form-group row">
                        <label class="col-sm-3">Address</label>
                        <div class="col-sm-9">
                            : {{$com->address}}
                        </div>
                    </div>
                </div>
                <div class="col-sm-5">
                    <img src="{{asset($com->logo)}}" alt="" width="150">
                </div>
            </div>
            <div class="row">
                <div class="col-sm-12">
                    <p>
                        <strong>Description</strong>
                    </p>
                    <div>
                        {{$com->description}}
                    </div>
                </div>
            </div>
        </div>
    </div>
@endsection 
@section('js')
    <script>
        $(document).ready(function(){
            $('#sidebar-menu li').removeClass('active open');
            $('#sidebar-menu li ul li').removeClass('active');

            $('#menu_config').addClass('active open');
            $('#collapse_config').addClass('collapse in');
            $('#menu_company').addClass('active');
        });
    </script>
@endsection