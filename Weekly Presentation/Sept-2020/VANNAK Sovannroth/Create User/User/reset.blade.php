@extends('admin::layouts.master')
@section('header')
    <strong>Reset Password</strong>
@endsection
@section('content')
    <form action="{{route('user.save')}}" method="POST"">
        @csrf
        <div class="card card-gray">
            <div class="toolbox">
                <button class="btn btn-primary btn-sm btn-oval">
                    <i class="fa fa-save"></i> Save
                </button>
                
            </div>
            <div class="card-block">
                @component('admin::coms.alert')
                @endcomponent
                <div class="row">
                    <div class="col-sm-8">
                        <div class="form-group row">
                            <label for="password" class="col-sm-3">New Password <span class="text-danger">*</span></label>
                            <div class="col-sm-9">
                                <input type="password" class="form-control" id="password" name="password" required>
                            </div>
                        </div>
                        <div class="form-group row">
                            <label for="cpassword" class="col-sm-3">Confirmed Password <span class="text-danger">*</span></label>
                            <div class="col-sm-9">
                                <input type="password" class="form-control" id="cpassword" name="cpassword" required>
                            </div>
                        </div>
                    </div>
                    
                </div>
            </div>
        </div>
    </form>
@endsection
